#define LOG_TAG "CHJCAR-N"

#include <nativehelper/JNIHelp.h>
#include <jni.h>
#include <atomic>
#include <cinttypes>
#include <limits.h>
#include <android_runtime/AndroidRuntime.h>
//#include <android_runtime/Log.h>
#include <utils/Log.h>
#include <nativehelper/ScopedLocalRef.h>



#include "../lib_diag/CHJCarDiagReader.h"
#include "../lib_diag/CHJCarDiagCommThread.h"
#include "../lib_diag/CHJCarDiagDTCMonitor.h"
#include "../lib_diag/CHJCarDiagDTCThread.h"



namespace android
{

#define DIAG_CLASS_NAME "com/android/car/chj/CHJCarDiagService"

static struct 
{
    jmethodID getUDSMessage;
} gServiceClassInfo;



class CHJCarNativeDiagManager : public virtual RefBase,
                                              public virtual CHJCarDiagReaderInterface
    
{
    public:
        CHJCarNativeDiagManager( jobject contextObj, jobject serviceObj );
        status_t start();
        status_t stop();
        status_t setMessage(    const char* mMsg );
        virtual void getUDSMessage( String8 mMessage );
        virtual void setPowerState( int powerState );

        int doSetSQIThresholdValue( int thresholdValue );
        int doGetSQIValue();
        int doGetSQIThresholdValue();
        int doGetEthLinkStatus();
        int doGetPhyId();
        int doSetPhyTestMode( int mode );
        int doGetCableStatus();
        void queryCableStatus();
        void resetPhyTestMode();
        void groupClearAllDTC();

    protected:
        virtual ~CHJCarNativeDiagManager();

    private:
        jobject mContextObj;
        jobject mServiceObj;

        sp<CHJCarDiagReader> mCHJCarDiagReader;
        sp<CHJCarDiagCommThread> mCHJCarDiagCommThread;

        sp<CHJCarDiagDTCMonitor> mCHJCarDiagMonitor;
        sp<CHJCarDiagDTCThread> mCHJCarDiagDTCThread;

        
    static inline JNIEnv* jniEnv() 
    {
        return AndroidRuntime::getJNIEnv();
    }
};

CHJCarNativeDiagManager::CHJCarNativeDiagManager(jobject contextObj,        jobject serviceObj)
{
    JNIEnv* env = jniEnv();

    mContextObj = env->NewGlobalRef(contextObj);
    mServiceObj = env->NewGlobalRef(serviceObj);

    mCHJCarDiagReader = new CHJCarDiagReader( this );
    mCHJCarDiagCommThread = new CHJCarDiagCommThread( mCHJCarDiagReader );

    mCHJCarDiagMonitor = new CHJCarDiagDTCMonitor( this, mCHJCarDiagReader );
    mCHJCarDiagDTCThread = new CHJCarDiagDTCThread( mCHJCarDiagMonitor );
    DIAG_D("%s__init CHJCarDiagReader and CHJCarDiagCommThread__",__func__);

}

CHJCarNativeDiagManager::~CHJCarNativeDiagManager()
{
    JNIEnv* env = jniEnv();

    env->DeleteGlobalRef( mContextObj );
    env->DeleteGlobalRef( mServiceObj );

    stop();
}

 status_t CHJCarNativeDiagManager::start()
{
    status_t result = mCHJCarDiagCommThread->run( "CHJCarDiagCommThread", PRIORITY_NORMAL );
    if ( result )
    {
        DIAG_E("Could not start CarDiagComm thread due to error %d.", result);
        return result;
    }

    result = mCHJCarDiagDTCThread->run( "CHJCarDiagDTCThread", PRIORITY_NORMAL );
    if ( result )
    {
        ALOGW("Could not start CarDiagDTC thread due to error %d.", result);
        mCHJCarDiagCommThread->requestExit();
        return result;
    }

    DIAG_D("start run CHJCarDiag two thread!");
    return OK;
}

 status_t CHJCarNativeDiagManager::stop()
 {
     status_t result = mCHJCarDiagCommThread->requestExitAndWait();
     if ( result )
     {
         DIAG_E("Could not stop CarDiagComm thread due to error %d.", result);
         return result;
     }

     result = mCHJCarDiagDTCThread->requestExitAndWait();
     if ( result )
     {
         DIAG_E("Could not stop CarDiagDTC thread due to error %d.", result);
         return result;
     }
     
     return OK;
 }

 status_t CHJCarNativeDiagManager::setMessage( const char* mMsg )
 {
     String8 mStrmsg = String8( mMsg );
     DIAG_D("GXDWDD received message from JAVA service :%s",mStrmsg.c_str());

     mCHJCarDiagReader->queueSendingMsg( mStrmsg );
     return OK;
 }

  void CHJCarNativeDiagManager::getUDSMessage( String8 mMessage )
 {
     JNIEnv* env = jniEnv();
     
     ScopedLocalRef<jstring> uniqueIdObj(env, env->NewStringUTF( mMessage ));
     env->CallObjectMethod( mServiceObj, gServiceClassInfo.getUDSMessage, uniqueIdObj.get() );
 }

 void CHJCarNativeDiagManager::setPowerState( int powerState )
 {
    mCHJCarDiagMonitor->setDrivingCycleState( powerState );
 }

 int CHJCarNativeDiagManager::doSetSQIThresholdValue( int thresholdValue )
 {
     return mCHJCarDiagMonitor->setSQILimitValue( thresholdValue );
 }

 int CHJCarNativeDiagManager::doGetSQIValue()
 {
     return mCHJCarDiagMonitor->getEthSQIValue();
 }

 int CHJCarNativeDiagManager::doGetSQIThresholdValue()
 {
     return mCHJCarDiagMonitor->getSQILimitValue();
 }

 int CHJCarNativeDiagManager::doGetEthLinkStatus()
 {
     return mCHJCarDiagMonitor->getLinkStatus();
 }

 int CHJCarNativeDiagManager::doGetPhyId()
 {
     return mCHJCarDiagMonitor->getPhyId();
 }

 int CHJCarNativeDiagManager::doSetPhyTestMode( int mode )
 {
     return mCHJCarDiagMonitor->setSQITestMode( mode );
 }

 void CHJCarNativeDiagManager::queryCableStatus()
 {
     mCHJCarDiagMonitor->queryCableStatus();
 }
 
 int CHJCarNativeDiagManager::doGetCableStatus()
 {
     return mCHJCarDiagMonitor->getCableStatus();
 }

 void CHJCarNativeDiagManager::resetPhyTestMode()
 {
     mCHJCarDiagMonitor->resetPhyTestModeStatus();
 }

 void CHJCarNativeDiagManager::groupClearAllDTC()
 {
    mCHJCarDiagMonitor->groupClearAllDTC();
 }

/********************************************NATIVE LAYER*******************************************************/
static jlong nativeDiagInit(JNIEnv* env, jclass /* clazz */, jobject serviceObj, jobject contextObj )
 {

    CHJCarNativeDiagManager* dm = new CHJCarNativeDiagManager(contextObj, serviceObj );
    dm->incStrong(0);

    DIAG_D("%s __init CHJCarNativeDiagManager__",__func__);
    return reinterpret_cast<jlong>( dm );
}



static void nativeDiagStart(JNIEnv* env, jclass /* clazz */, jlong ptr) 
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);

    status_t result = dm->start();
    if ( result )
    {
        jniThrowRuntimeException( env, "Diag Native Manager could not be started.");
    }
    
    DIAG_D("%s __start CHJCarNativeDiagManager_",__func__);

}

static void nativeDiagSendMessage( JNIEnv *env, jclass /*clazz*/, jstring jmsg, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    const char* pDIDMsg = env->GetStringUTFChars( jmsg, NULL );
    if ( pDIDMsg )
    {
        status_t result = dm->setMessage( pDIDMsg );

        env->ReleaseStringUTFChars( jmsg, pDIDMsg );
    }

}

static void nativeSetPowerState( JNIEnv *env, jclass /*clazz*/, jint driverCircle, jlong ptr)
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    dm->setPowerState( driverCircle );
}

static jint nativeSetSQIThresholdValue( JNIEnv *env, jclass /*clazz*/, jint thresholdValue, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doSetSQIThresholdValue( thresholdValue );
}

static jint nativeGetSQIValue( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doGetSQIValue();
}

static jint nativeGetSQIThresholdValue( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doGetSQIThresholdValue();
}

static jint nativeGetEthLinkStatus( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doGetEthLinkStatus();
}

static jint nativeGetPhyId( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doGetPhyId();
}

static jint nativeSetPhyTestMode( JNIEnv *env, jclass /*clazz*/, jint mode, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doSetPhyTestMode( mode );
}

static jint nativeGetCableStatus( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    return dm->doGetCableStatus();
}

static void nativeQueryCableStatus( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    dm->queryCableStatus();
}

static void nativeResetPhyTestMode( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    dm->resetPhyTestMode();
}

static void nativeClearAllDTC( JNIEnv *env, jclass /*clazz*/, jlong ptr )
{
    CHJCarNativeDiagManager* dm = reinterpret_cast<CHJCarNativeDiagManager*>(ptr);
    dm->groupClearAllDTC();
}

static const JNINativeMethod sDiagNativeMethods[] =
{
    { "nativeDiagInit",
            "(Lcom/android/car/chj/CHJCarDiagService;Landroid/content/Context;)J",
            (void*) nativeDiagInit },
    { "nativeDiagStart", 
            "(J)V",  
            (void*) nativeDiagStart },
    { "nativeDiagSendMessage",
            "(Ljava/lang/String;J)V",
            (void*) nativeDiagSendMessage},
    { "nativeSetPowerState",
            "(IJ)V",
            (void*) nativeSetPowerState},
    { "nativeSetSQIThresholdValue",
            "(IJ)I",
            (void*) nativeSetSQIThresholdValue},
    { "nativeGetSQIValue",
            "(J)I",
            (void*) nativeGetSQIValue},
    { "nativeGetSQIThresholdValue",
            "(J)I",
            (void*) nativeGetSQIThresholdValue},
    { "nativeGetEthLinkStatus",
            "(J)I",
            (void*) nativeGetEthLinkStatus},
    { "nativeGetPhyId",
            "(J)I",
            (void*) nativeGetPhyId},
    { "nativeSetPhyTestMode",
            "(IJ)I",
            (void*) nativeSetPhyTestMode},
    { "nativeGetCableStatus",
            "(J)I",
            (void*) nativeGetCableStatus},
    { "nativeQueryCableStatus",
            "(J)V",
            (void*) nativeQueryCableStatus},
    { "nativeResetPhyTestMode",
            "(J)V",
            (void*) nativeResetPhyTestMode},
    { "nativeClearAllDTC",
            "(J)V",
            (void*) nativeClearAllDTC}

};


#define GET_METHOD_ID(var, clazz, methodName, methodDescriptor) \
        var = env->GetMethodID(clazz, methodName, methodDescriptor); \
        LOG_FATAL_IF(! (var), "Unable to find method " methodName);

#define GET_FIELD_ID(var, clazz, fieldName, fieldDescriptor) \
        var = env->GetFieldID(clazz, fieldName, fieldDescriptor); \
        LOG_FATAL_IF(! (var), "Unable to find field " fieldName);

int register_com_android_diag_native_manager( JNIEnv* env ) 
{
    int retVal;
    
    jclass clazz = env->FindClass( DIAG_CLASS_NAME );
    if ( !clazz )
    {
        DIAG_E("___CHJ_DIAG_ can not found CHJCarDiagService ____");
        return JNI_ERR;
    }
    
    retVal = jniRegisterNativeMethods(env, DIAG_CLASS_NAME, sDiagNativeMethods, NELEM(sDiagNativeMethods));
    if( retVal<0 )
    {
        DIAG_E("___CHJ_DIAG_ can not registe JNI Methods ____");
        return retVal;
    }

    GET_METHOD_ID( gServiceClassInfo.getUDSMessage , clazz, "getUDSMessage", "(Ljava/lang/String;)V");

    return 0;
}

}


using namespace android;
 extern "C" jint JNI_OnLoad(JavaVM* jvm, void*) 
{
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void**) &env, JNI_VERSION_1_6)) 
    {
        return JNI_ERR;
    }


    if ( register_com_android_diag_native_manager(env) == -1 ) 
    {
        return JNI_ERR;
    }
    
    return JNI_VERSION_1_6;
}



