/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with THUNDERSOFT in writing by applicable law.
 */
#define LOG_TAG "CarPowerManagerNativeheshang"

#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Log.h>

#include "CarPowerManager.h"

namespace android {

// Public functions

void CarPowerManager::test() {
    ALOGI("%s: only test func run!", __FUNCTION__);
}

int CarPowerManager::registerPowerEventListener(BnPowerEventListener *listener) {
    int ret = -1;
    ALOGE("%s: registerPowerEventListener!", __FUNCTION__);
    if (listener == nullptr) {
        ALOGE("%s: listener must not be null", __FUNCTION__);
    }
    if (connectToCarService()) {
        mService->registerPowerEventListener(listener);
        ret = 0;
    }
    return ret;
}

int CarPowerManager::unregisterPowerEventListener(BnPowerEventListener *listener) {
    int ret = -1;
    ALOGE("%s: unregisterPowerEventListener!", __FUNCTION__);
    if (listener == nullptr) {
        ALOGE("%s: listener must not be null", __FUNCTION__);
    }
    if (mIsConnected) {
        mService->unregisterPowerEventListener(listener);
        ret = 0;
    }
    return ret;
}

// Private functions
bool CarPowerManager::connectToCarService() {
    if (mIsConnected) {
        // Service is already connected
        return true;
    }

    const String16 ICarName("car_service");
    const String16 ICarPowerName("car_power_service");
    ALOGE("%s: Connecting to CarService", __FUNCTION__);

    // Get ICar
    sp<IServiceManager> serviceManager = defaultServiceManager();
    if (serviceManager == nullptr) {
        ALOGE("%s: Cannot get defaultServiceManager", __FUNCTION__);
        return false;
    }

    sp<IBinder> binder = (serviceManager->getService(ICarName));
    if (binder == nullptr) {
        ALOGE("%s: Cannot get ICar", __FUNCTION__);
        return false;
    }

    // Get ICarPowerManager
    sp<ICar> iCar = interface_cast<ICar>(binder);
    if (iCar == nullptr) {
        ALOGE("%s: car service unavailable", __FUNCTION__);
        return false;
    }

    iCar->getCarService(ICarPowerName, &binder);
    if (binder == nullptr) {
        ALOGE("%s: Cannot get ICarPowerManager mService", __FUNCTION__);
        return false;
    }

    mService = interface_cast<ICarPowerManager>(binder);
    if (mService == nullptr) {
        ALOGW("%s: car power management service unavailable", __FUNCTION__);
        return false;
    }
    mIsConnected = true;
    ALOGE("%s: Connecting to CarService successfull!", __FUNCTION__);
    return true;
}

} // namespace android
