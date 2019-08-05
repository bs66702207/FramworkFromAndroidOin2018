硬件访问服务:
    Android驱动开发_硬件访问服务.jpg介绍的是传统的HAL层(Android O之前)，虽然APP可以通过jni load C库来达到直接操作硬件的目的，但是对于display、audio等来说，还是需要一个统一的服务进行管理，然后APP1、APP2、APP3通过system_server来访问。
    硬件访问服务流程
1. loadLibrary - 加载C库
2. JNI_OnLoad - 注册本地方法，分别调用各个硬件的函数来注册本地方法: LED、振动器、串口
3. SystemServer对每个硬件构造Service、addService
4. APP获得服务getService、使用服务执行Service方法

    硬件访问服务开发
1. JNI和HAL com_android_server_LedService.cpp 注册JNI本地方法，加载hal_led.c(open、read、write访问驱动)
2. 修改onload.cpp，调用com_android_server_LedService.cpp实现的函数register_android_server_LedService
3. 修改SystemService.java，ServiceManager.addService("led", new LedService());
4. LedService.java 调用本地方法
5. ILedService.java(ILedService.aidl) 给APP使用

HAL module code flow:

//1 so库文件的加载
hardware/libhardware/hardware.c

static const char *variant_keys[] = {
    "ro.hardware",  /* This goes first so that it can pick up a different file on the emulator. */
    "ro.product.board",
    "ro.board.platform",
    "ro.arch"
};

hw_get_module("led", (hw_module_t const**)&module);
hw_get_module_by_class(id, NULL, module) {//先找到哪个算哪个
    property_get(prop_name, prop, NULL);//ro.hardware.led
    hw_module_exists(path, sizeof(path), name, prop);
    for() property_get(variant_keys[i], prop, NULL);//ro.hardware=tiny4412, ro.product.board=tiny4412, ro.board.platform=exynos4, ro.arch=没有设置
    hw_module_exists(path, sizeof(path), name, prop);
    hw_module_exists(path, sizeof(path), name, "default");//都没有的话，看看能不能找到led.default.so
    return load(class_id, path, module);//dlopen
}

/*它用来判断"name"."subname".so文件是否存在
#if defined(__LP64__)
#define HAL_LIBRARY_PATH1 "/system/lib64/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib64/hw"
#define HAL_LIBRARY_PATH3 "/odm/lib64/hw"
#else
#define HAL_LIBRARY_PATH1 "/system/lib/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib/hw"
#define HAL_LIBRARY_PATH3 "/odm/lib/hw"
#endif

led.tiny4412.so
led.exynos4.so
led.default.so
*/
static int hw_module_exists(char *path, size_t path_len, const char *name, const char *subname)

/*
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .id = "led",
    .methods = &led_module_methods,
};
*/
static int load(const char *id, const char *path, const struct hw_module_t **pHmi) {
    struct hw_module_t *hmi = NULL;
    handle = dlopen(path, RTLD_NOW);
    const char *sym = HAL_MODULE_INFO_SYM_AS_STR;//"HMI"
    hmi = (struct hw_module_t *)dlsym(handle, sym);//从SO文件中获得名为HMI的hw_module_t结构体
    if (strcmp(id, hmi->id) != 0)//判断名字是否一致(hmi->id, "led")
    *pHmi = hmi;
}

//2 JNI怎么使用HAL
com_android_server_LedService.cpp
jint ledOpen(JNIEnv *env, jobject cls) {
    jint err;
    hw_module_t* module;
    hw_device_t* device;
    err = hw_get_module("led", (hw_module_t const**)&module);//hw_get_module 获得一个hw_module_t结构体
    err = module->methods->open(module, NULL, &device);//获得一个hw_device_t结构体
    led_device->led_open(led_device);//把hw_device_t结构体转换为设备自定义的结构体
}

//3 HAL怎么写
led_hal.c
//3.1 实现一个名为HMI的hw_module_t结构体
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .id = "led",
    .methods = &led_module_methods,
};
//3.2 实现一个open函数, 它会根据name返回一个设备自定义的结构体
static struct led_device_t led_dev = {//这个设备自定义的结构体的第1个成员是 hw_device_t结构体，还可以定义设备相关的成员
    .common = {
        .tag   = HARDWARE_DEVICE_TAG,
        .close = led_close,
    },
    .led_open  = led_open,
    .led_ctrl  = led_ctrl,
};
static int led_device_open(const struct hw_module_t* module, const char* id,
        struct hw_device_t** device)
{
    *device = &led_dev;
    return 0;
}
static struct hw_module_methods_t led_module_methods = {
    .open = led_device_open,
};

//使用反射访问硬件服务
APP_0001_LEDDemo.git
git checkout v8  // 使用反射Reflect

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
//import android.os.ILedService;
//import android.os.ServiceManager;
import android.os.IBinder;

//private ILedService iLedService = null;
Object proxy = null;
Method ledCtrl = null;

//iLedService = ILedService.Stub.asInterface(ServiceManager.getService("led"));
Method getService = Class.forName("android.os.ServiceManager").getMethod("getService", String.class);
Object ledService = getService.invoke(null, "led");
Method asInterface = Class.forName("android.os.ILedService$Stub").getMethod("asInterface", IBinder.class);
proxy = asInterface.invoke(null, ledService);
ledCtrl = Class.forName("android.os.ILedService$Stub$Proxy").getMethod("ledCtrl", int.class, int.class);

//iLedService.ledCtrl(0, 1);
ledCtrl.invoke(proxy, 0, 1);

app/build.gradle
-    compile project(':classes')
+    provided project(':classes')
是提供给那些只编译不打包场景的命令。就是，我在编译的时候对某一个jar文件有依赖，但是最终打包apk文件时，我不想把这个jar文件放进去，可以用这个命令
