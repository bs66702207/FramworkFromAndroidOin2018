灯光系统:

/***** 1 框架 *****/
视频里用的jni + hw_get_module
Android P用的是jni + hw_binder
但是思路还是一样的，为set_light提供不同的set_light函数
set_light_backlight //背光灯
set_light_battery //电池灯
set_light_notifications //通知灯

frameworks/base/services/core/jni/com_android_server_lights_LightsService.cpp
hardware/interfaces/light/2.0/default/Light.cpp
hardware/qcom/display/liblight/lights.c
kernel/msm-4.14/drivers/leds/led-class.c //内核已经做好了led的框架

/***** 2 led_class驱动 *****/
在驱动层，我们需要实现led的硬件操作

git clone https://github.com/weidongshan/DRV_0001_LEDS.git
git pull origin
git checkout v2 //use led class

echo 255 > /sys/class/leds/led1/brightness
cat /sys/class/leds/led1/brightness
cat /sys/class/leds/led1/max_brightness

闪烁
echo timer > /sys/class/leds/led1/trigger
echo 100 > /sys/class/leds/led1/delay_on //亮100ms
echo 200 > /sys/class/leds/led1/delay_off //灭100ms

关闭
echo 0 > /sys/class/leds/led1/delay_on
或
echo 0 > /sys/class/leds/led1/brightness

分析闪烁功能:
echo timer > /sys/class/leds/led1/trigger  // timer对应 ledtrig-timer.c

kernel/msm-4.14/drivers/leds/led-triggers.c
ssize_t led_trigger_store(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct led_trigger *trig;
    int ret = count;

    mutex_lock(&led_cdev->led_access);

    if (led_sysfs_is_disabled(led_cdev)) {
        ret = -EBUSY;
        goto unlock;
    }

    if (sysfs_streq(buf, "none") &&
            !(led_cdev->flags & LED_KEEP_TRIGGER)) {//buf = "none"的话什么都不做，返回
        led_trigger_remove(led_cdev);
        goto unlock;
    }

    down_read(&triggers_list_lock);
    list_for_each_entry(trig, &trigger_list, next_trig) {//1. 从trigger_list找出名为"timer"的trigger
        if (sysfs_streq(buf, trig->name)) {
            down_write(&led_cdev->trigger_lock);

            led_trigger_set(led_cdev, trig);// 2. 调用
            {//drivers/leds/trigger/ledtrig-timer.c, void led_trigger_set(struct led_classdev *led_cdev, struct led_trigger *trig)
                // 3. 把trigger放入led_classdev的trig_list链表里
		        list_add_tail(&led_cdev->trig_list, &trigger->led_cdevs);
		        led_cdev->trigger = trigger;
                // 4.
                trig->activate(led_cdev);
                {//5. 对于"timer": drivers/leds/trigger/ledtrig-timer.c, static void timer_trig_activate(struct led_classdev *led_cdev)
                    // 6. 创建2个文件: delay_on, delay_off
                    device_create_file
                    device_create_file
                    led_blink_set(led_cdev, &led_cdev->blink_delay_on, &led_cdev->blink_delay_off);// 让LED闪烁，初始化没有设置所以是0，传到led-core.c，默认是500ms
                      -> led_blink_setup
                        -> led_set_software_blink //最后定时器mod_timer来实现闪烁的功能
                }
            }

            up_write(&led_cdev->trigger_lock);

            up_read(&triggers_list_lock);
            goto unlock;
        }
    }
    /* we come here only if buf matches no trigger */
    ret = -EINVAL;
    up_read(&triggers_list_lock);

unlock:
    mutex_unlock(&led_cdev->led_access);
    return ret;
}

echo 100 > /sys/class/leds/led1/delay_on
led_delay_on_store
  state = simple_strtoul(buf, &after, 10);
	led_blink_set  // // 让LED闪烁
	led_cdev->blink_delay_on = state;

echo 200 > /sys/class/leds/led1/delay_off
led_delay_off_store
	state = simple_strtoul(buf, &after, 10);
	led_blink_set // 让LED闪烁
	led_cdev->blink_delay_off = state;

//led_devs[i].cdev.default_trigger = "timer"; //默认使能闪烁，不需要写sys节点

/***** 3 编写android灯光系统的hal程序 *****/
Android灯光系统_背光灯.jpg
Java: frameworks/base/services/core/java/com/android/server/lights/LightsService.java
JNI:  frameworks/base/services/core/jni/com_android_server_lights_LightsService.cpp
Hal:  lights.c

默认配色: frameworks/base/core/res/res/values/config.xml
电池灯: frameworks/base/services/core/java/com/android/server/BatteryService.java
通知灯: frameworks/base/services/core/java/com/android/server/notification/NotificationManagerService.java

怎么写LIGHTS HAL
a. 实现一个名为HMI的hw_module_t结构体
b. 实现一个open函数, 它会根据name返回一个light_device_t结构体
c. 实现多个light_device_t结构体，每一个对应一个DEVICE
   light_device_t结构体里第1个成员是hw_device_t结构体, 紧接着一个set_light函数

git clone https://github.com/weidongshan/SYS_0002_Lights.git
git pull origin
git checkout v1 //在google上下载lights.c修改为lights_sony.c，在它基础上修改

lights.h
struct light_state_t {
    unsigned int color;// 把灯设为什么颜色, 或 把LCD的亮度设为什么

    int flashMode; // 是否闪烁, LIGHT_FLASH_NONE表示不闪，这个时候color表示是亮还是灭，亮的颜色是什么
    int flashOnMS; // 亮的时间
    int flashOffMS; // 灭的时间

    /**
     * Policy used by the framework to manage the light's brightness.
     * Currently the values are BRIGHTNESS_MODE_USER and BRIGHTNESS_MODE_SENSOR.
     */
    int brightnessMode; // 表示LCD的背光亮度模式，亮度值可以从color算出来
};


/***** 4 电池灯使用分析 *****/
Android灯光系统_电池灯.jpg
frameworks/base/services/core/java/com/android/server/BatteryService.java
private final class HealthHalCallback extends IHealthInfoCallback.Stub
        implements HealthServiceWrapper.Callback {
    @Override
    public void healthInfoChanged(android.hardware.health.V2_0.HealthInfo props) {
        BatteryService.this.update(props);
    }
...
}

private void update(android.hardware.health.V2_0.HealthInfo info) {
    traceBegin("HealthInfoUpdate");
    synchronized (mLock) {
        if (!mUpdatesStopped) {
            mHealthInfo = info.legacy;
            // Process the new values.
            processValuesLocked(false);
            mLock.notifyAll(); // for any waiters on new info
        } else {
            copy(mLastHealthInfo, info.legacy);
        }
    }
    traceEnd();
}

private void processValuesLocked(boolean force) {
...
    sendBatteryChangedIntentLocked();//发出广播消息 APP0发出通知，ACTION_BATTERY_CHANGED，比如PowerManagerService会关心这个广播
/* PMS
onReceive
    handleBatteryStateChangedLocked
        updatePowerStateLocked
*/
    mLed.updateLightsLocked();//发出完通知之后，就调用灯光的函数，Update the battery LED
}

public void updateLightsLocked() {
    final int level = mHealthInfo.batteryLevel;
    final int status = mHealthInfo.batteryStatus;
    if (level < mLowBatteryWarningLevel) {
        if (status == BatteryManager.BATTERY_STATUS_CHARGING) {
            // Solid red when battery is charging
            mBatteryLight.setColor(mBatteryLowARGB);//最终调用到frameworks/base/services/core/java/com/android/server/lights/LightsService.java
        } else {
            // Flash red when battery is low and not charging
            mBatteryLight.setFlashing(mBatteryLowARGB, Light.LIGHT_FLASH_TIMED,
                    mBatteryLedOn, mBatteryLedOff);
        }
    } else if (status == BatteryManager.BATTERY_STATUS_CHARGING
            || status == BatteryManager.BATTERY_STATUS_FULL) {
        if (status == BatteryManager.BATTERY_STATUS_FULL || level >= 90) {
            // Solid green when full or charging and nearly full
            mBatteryLight.setColor(mBatteryFullARGB);
        } else {
            // Solid orange when charging and halfway full
            mBatteryLight.setColor(mBatteryMediumARGB);
        }
    } else {
        // No lights if not charging and not low
        mBatteryLight.turnOff();
    }
}

/***** 5 通知灯使用分析 *****/

frameworks/base/services/core/java/com/android/server/notification/NotificationManagerService.java
private Light mNotificationLight;
void init(...) {
    mNotificationLight = lightsManager.getLight(LightsManager.LIGHT_ID_NOTIFICATIONS);
}
void updateLightsLocked()//对于通知灯的所有操作都是通过这个函数实现的，由于有很多地方调用，为了便于分析，我们从APP调用的接口查起

NotificationManager nm = ( NotificationManager ) getSystemService( NOTIFICATION_SERVICE );
Notification notif = new Notification();
notif.ledARGB = 0xFFff0000;
notif.flags = Notification.FLAG_SHOW_LIGHTS;
notif.ledOnMS = 100;
notif.ledOffMS = 100;
nm.notify(LED_NOTIFICATION_ID, notif);
  -> ... -> service.enqueueNotificationWithTag(pkg, mContext.getOpPackageName(), tag, id, copy, user.getIdentifier());
    -> enqueueNotificationInternal(pkg, opPkg, Binder.getCallingUid(), Binder.getCallingPid(), tag, id, notification, userId);
      -> mHandler.post(new EnqueueNotificationRunnable(userId, r));
        -> mHandler.post(new PostNotificationRunnable(r.getKey()));
          -> buzzBeepBlinkLocked(r);//r里面有Notification成员
void buzzBeepBlinkLocked(NotificationRecord record) {
...
    if (record.getLight() != null && aboveThreshold && ((record.getSuppressedVisualEffects() & SUPPRESSED_EFFECT_LIGHTS) == 0)) {//如果是闪灯的话
        updateLightsLocked();
}
void updateLightsLocked() {
    if (ledNotification == null || mInCall || mScreenOn) {//当我们正在通话或者亮屏时，不会起作用的，直接关闭通知灯
            mNotificationLight.turnOff();
    } else {//那么只有在黑屏的情况下
        NotificationRecord.Light light = ledNotification.getLight();//里面有颜色，时间值等
        mNotificationLight.setFlashing(light.color, Light.LIGHT_FLASH_TIMED, light.onMs, light.offMs);
    }
}

实验
git clone https://github.com/weidongshan/APP_0002_LIGHTDemo.git
git pull origin
git checkout v1 //黑屏下测试，黑屏之前点击按钮20s后开始运行

通知灯使用过程:
a. SystemServer.java : 注册Notification服务
b. app的上下文context里有静态块，它会注册服务: registerService(NOTIFICATION_SERVICE)
c. app: nm = getSystemService
d. 构造Notification
e. 设置参数: 通知类型、颜色、时间
f. nm.notify
   f.1 getService 得到的是 "SystemServer注册的Notification服务"
   f.2 最终判断通知类型进而调用到通知灯的JNI函数

/***** 6 背光灯使用分析 *****/

//frameworks/base/services/core/java/com/android/server/display/DisplayManagerService.java
DisplayBlanker blanker = new DisplayBlanker() {//实例化DisplayBlanker
    @Override
    public void requestDisplayState(int state, int brightness) {
        // The order of operations is important for legacy reasons.
        if (state == Display.STATE_OFF) {
            requestGlobalDisplayStateInternal(state, brightness);
        }

        callbacks.onDisplayStateChange(state);

        if (state != Display.STATE_OFF) {
            requestGlobalDisplayStateInternal(state, brightness);
        }
    }
};
mDisplayPowerController = new DisplayPowerController(mContext, callbacks, handler, sensorManager, blanker);

//frameworks/base/services/core/java/com/android/server/display/DisplayPowerController.java
private DisplayPowerState mPowerState;//利用这个实例调节背光
private void initialize() {
    mPowerState = new DisplayPowerState(mBlanker, mColorFadeEnabled ? new ColorFade(Display.DEFAULT_DISPLAY) : null);
}

//frameworks/base/services/core/java/com/android/server/display/DisplayPowerState.java
private final PhotonicModulator mPhotonicModulator;
public DisplayPowerState(DisplayBlanker blanker, ColorFade colorFade) {
    mBlanker = blanker;
    mPhotonicModulator = new PhotonicModulator();
    mPhotonicModulator.start();//启动PhotonicModulator的run()
}

//frameworks/base/services/core/java/com/android/server/display/DisplayPowerState.java
private final class PhotonicModulator extends Thread {

    public boolean setState(int state, int backlight) {
        mLock.notifyAll();
    }

    public void run() {//在这个里面调节
        for (;;) {
            mLock.wait();
            mBlanker.requestDisplayState(state, backlight);//又回到DisplayManagerService里的requestDisplayState
        }
    }   
}

//frameworks/base/services/core/java/com/android/server/display/DisplayManagerService.java
private void requestGlobalDisplayStateInternal(int state, int brightness) {
    if (state == Display.STATE_UNKNOWN) {
        state = Display.STATE_ON;
    }
    if (state == Display.STATE_OFF) {
        brightness = PowerManager.BRIGHTNESS_OFF;
    } else if (brightness < 0) {
        brightness = PowerManager.BRIGHTNESS_DEFAULT;
    } else if (brightness > PowerManager.BRIGHTNESS_ON) {
        brightness = PowerManager.BRIGHTNESS_ON;
    }

    synchronized (mTempDisplayStateWorkQueue) {
        try {
                mGlobalDisplayState = state;
                mGlobalDisplayBrightness = brightness;
                applyGlobalDisplayStateLocked(mTempDisplayStateWorkQueue);//我们只关心背光部分
        }
    }
}

applyGlobalDisplayStateLocked
  -> updateDisplayStateLocked
    -> requestDisplayStateLocked
//frameworks/base/services/core/java/com/android/server/display/LocalDisplayAdapter.java
public Runnable requestDisplayStateLocked(final int state, final int brightness) {
    mBacklight.setBrightness(brightness);

}

查找一下PhotonicModulator里面的setState
    setState <- mHandler.post(mScreenUpdateRunnable) <- postScreenUpdateThreadSafe <- scheduleScreenUpdate
我们发现scheduleScreenUpdate在四个地方被用到
1. 构造DisplayPowerState时
2. setScreenState //设置mScreenState和mScreenReady
3. setScreenBrightness //设置mScreenBrightness和mScreenReady
4. setColorFadeLevel //设置mColorFadeReady和mScreenReady
    然后通过scheduleScreenUpdate来处理这些变量

那么是谁来触发这些方法的调用呢，我们从入口查找/*PowerManagerService*/
frameworks/base/services/core/java/com/android/server/power/PowerManagerService.java
里面注册了4个Receiver，1个ContentObserver(APP可以修改里面的变量)，最终都会调用updatePowerStateLocked
在Phase 3里面更新显示电源状态，我们只关心这块
private void updatePowerStateLocked() 
  -> updateDisplayPowerStateLocked(dirtyPhase2);
    -> mDisplayManagerInternal.requestPowerState(mDisplayPowerRequest, mRequestWaitForNegativeProximity);
//frameworks/base/services/core/java/com/android/server/display/DisplayManagerService.java
private final class LocalService extends DisplayManagerInternal {
    @Override
    public boolean requestPowerState(DisplayPowerRequest request, boolean waitForNegativeProximity) {
        synchronized (mSyncRoot) {
            return mDisplayPowerController.requestPowerState(request, waitForNegativeProximity);
        }
    }
}
//frameworks/base/services/core/java/com/android/server/display/DisplayPowerController.java
public boolean requestPowerState(DisplayPowerRequest request, boolean waitForNegativeProximity) {
    sendUpdatePowerStateLocked();//send MSG_UPDATE_POWER_STATE
}

public void handleMessage(Message msg) {
    switch (msg.what) {
        case MSG_UPDATE_POWER_STATE:
            updatePowerState();
            break;

private void updatePowerState() {
    if (initialRampSkip || hasBrightnessBuckets
           || wasOrWillBeInVr || !isDisplayContentVisible || brightnessIsTemporary) {
       animateScreenBrightness(brightness, 0);
    } else { 
       animateScreenBrightness(brightness,
               slowChange ? mBrightnessRampRateSlow : mBrightnessRampRateFast);
    }
}

mScreenBrightnessRampAnimator = new RampAnimator<DisplayPowerState>(mPowerState, DisplayPowerState.SCREEN_BRIGHTNESS);

animateScreenBrightness
  -> mScreenBrightnessRampAnimator.animateTo(target, rate)//动画渐变的方式改变，以xx频率慢慢的调整过去
    -> Property.setValue(mObject, target);

public static final IntProperty<DisplayPowerState> SCREEN_BRIGHTNESS =
        new IntProperty<DisplayPowerState>("screenBrightness") {
    @Override
    public void setValue(DisplayPowerState object, int value) {
        object.setScreenBrightness(value);
    }

    @Override
    public Integer get(DisplayPowerState object) {
        return object.getScreenBrightness();
    }
};

实验
你可以参考android-er.blogspot.com/2011/02/change-system-screen-brightness-using.html来编写测试程序
git clone https://github.com/weidongshan/APP_0002_LIGHTDemo.git
git pull origin
git checkout v2  //v2, control backlight

但是程序会崩溃，网上查了下，虽然在xml里声明了写权限，但是还是需要在设置里面把它修改背光成员值的权限打开
自动调解背光使能的话，在用手滑动

下面我们看下系统设置里面的背光调解代码Setting -> Dispaly -> Brightness level : BrightnessDialog.java
//frameworks/base/packages/SystemUI/src/com/android/systemui/settings/BrightnessDialog.java
final ToggleSliderView slider = findViewById(R.id.brightness_slider);
mBrightnessController = new BrightnessController(this, icon, slider);
mBrightnessController.registerCallbacks();
//frameworks/base/packages/SystemUI/src/com/android/systemui/settings/BrightnessController.java
registerCallbacks
 -> mBackgroundHandler.post(mStartListeningRunnable);
   -> {
            mBrightnessObserver.startObserving();
            mUpdateModeRunnable.run();
            mUpdateSliderRunnable.run();
            mHandler.sendEmptyMessage(MSG_ATTACH_LISTENER); -> mControl.setOnChangedListener(BrightnessController.this);//假设滑动了滑动块会导致onChanged调用
      }

public void onChanged(ToggleSlider toggleSlider, boolean tracking, boolean automatic, int value, boolean stopTracking) {
    setBrightness(val);//滑动过程中，直接setBrightness，mDisplayManager.setTemporaryBrightness(brightness)，最终导致updatePowerState调用
    if (!tracking) {//如果松手了，那么就写到数据库里
        AsyncTask.execute(new Runnable() {
            public void run() {
                Settings.System.putIntForUser(mContext.getContentResolver(),
                        setting, val, UserHandle.USER_CURRENT);//也会导致updatePowerState调用
            }
        });
    }
}
