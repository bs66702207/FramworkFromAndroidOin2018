#define LOG_TAG "PowerStateMachineImplJni"

#include <nativehelper/JNIHelp.h>
#include <jni.h>
#include <atomic>
#include <cinttypes>
#include <limits.h>
#include <android_runtime/AndroidRuntime.h>
//#include <android_runtime/Log.h>
#include <utils/Log.h>
#include <nativehelper/ScopedLocalRef.h>
#include <suspend/autosuspend.h>

namespace android
{
#define POWER_STATE_MACHINE_IMPL_CLASS_NAME "com/tsdl/car/power/PowerStateMachineImpl"

static jint nativeForceSuspend(JNIEnv* /* env */, jclass /* clazz */) {
    jint ret = autosuspend_force_suspend();
    ALOGI("nativeForceSuspend returned %d", ret);
    return ret;
}

static const JNINativeMethod sPowerStateMachineImplNativeMethods[] = {
    /* name, signature, funcPtr */
    { "nativeForceSuspend", "()I",
         (void*) nativeForceSuspend },
};

int register_com_tsdl_car_power_PowerStateMachineImplNativeMethod(JNIEnv* env) {
    int retVal;

    retVal = jniRegisterNativeMethods(env, POWER_STATE_MACHINE_IMPL_CLASS_NAME, sPowerStateMachineImplNativeMethods, NELEM(sPowerStateMachineImplNativeMethods));
    if(retVal < 0) {
        ALOGE("___LIBSUSPEND_NATIVE_ can not registe JNI Methods ____");
        return JNI_ERR;
    }

    return 0;
}

}/* namespace android */

using namespace android;
 extern "C" jint JNI_OnLoad(JavaVM* jvm, void*)
{
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void**) &env, JNI_VERSION_1_6))
    {
        return JNI_ERR;
    }


    if ( register_com_tsdl_car_power_PowerStateMachineImplNativeMethod(env) == -1 )
    {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
