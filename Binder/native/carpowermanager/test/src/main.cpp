/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with THUNDERSOFT in writing by applicable law.
 */


#define LOG_TAG "PowerTestServiceheshang"

#include <signal.h>
#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>

#include "android/car/ICar.h"
//#include "com/tsdl/car/power/BnPowerEventListener.h"
#include "com/tsdl/car/power/ICarPowerManager.h"
#include "../CarPowerManager.h"

using namespace android;
using namespace android::binder;
using namespace android::car;
using namespace com::tsdl::car::power;

const char* PM_STATE_NAME[6] = {"UNPOWERED", "PARTLYWORK", "NORMAL", "PRESLEEP", "SLEEP", "ABNORMAL"};

static std::atomic_bool run(true);

class CarPowerEventListenerImpl final : public CarPowerManager::PowerEventListener {

    int count = 0;

public:
    Status onPowerStateChanged(int32_t previousState, int32_t currentState) {
        ALOGE(" %s: %s -> %s", __FUNCTION__, PM_STATE_NAME[previousState], PM_STATE_NAME[currentState]);
        count ++;
        if(count > 10) {
            ALOGE(" %s: has test 10 times, exit!\n", __FUNCTION__);
            run = false;
        }
        return binder::Status::ok();
    };

};

int main(int, char**)
{

    CarPowerEventListenerImpl *mListener = new CarPowerEventListenerImpl();

    sp<ProcessState> processSelf(ProcessState::self());
    processSelf->startThreadPool();
    ALOGE("started");

    std::unique_ptr<CarPowerManager> carPowerManager(new CarPowerManager());

    carPowerManager->test();

    carPowerManager->registerPowerEventListener(mListener);

    do {
        sleep(5);
    } while (run);

    carPowerManager->unregisterPowerEventListener(mListener);
    delete mListener;
    mListener = nullptr;

    // Wait for threads to finish, and then exit.
    IPCThreadState::self()->joinThreadPool();
    ALOGE("joined and going down");
    return 0;
}
