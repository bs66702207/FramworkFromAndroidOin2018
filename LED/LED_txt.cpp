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
    /**
     * The color of the LED in ARGB.
     *
     * Do your best here.
     *   - If your light can only do red or green, if they ask for blue,
     *     you should do green.
     *   - If you can only do a brightness ramp, then use this formula:
     *      unsigned char brightness = ((77*((color>>16)&0x00ff))
     *              + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
     *   - If you can only do on or off, 0 is off, anything else is on.
     *
     * The high byte should be ignored.  Callers will set it to 0xff (which
     * would correspond to 255 alpha).
     */
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







