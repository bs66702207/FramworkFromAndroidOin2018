/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with THUNDERSOFT in writing by applicable law.
 */

#ifndef CAR_POWER_MANAGER
#define CAR_POWER_MANAGER

#include <utils/RefBase.h>

#include "android/car/ICar.h"
#include "com/tsdl/car/power/BnPowerEventListener.h"
#include "com/tsdl/car/power/ICarPowerManager.h"

using namespace android::car;
using namespace com::tsdl::car::power;

namespace android {

class CarPowerManager : public RefBase {
public:

    CarPowerManager()
    {
        ALOGE("%s: construction!", __FUNCTION__);
        mIsConnected = false;
    }

    virtual ~CarPowerManager() = default;

    void test();

    class PowerEventListener : public BnPowerEventListener {};

    // Set the callback function. This will execute in the binder thread.
    // Returns 0 on success
    int registerPowerEventListener(BnPowerEventListener *listener);

    // Returns 0 on success
    int unregisterPowerEventListener(BnPowerEventListener *listener);

private:
    bool connectToCarService();
    sp<ICarPowerManager> mService;
    bool mIsConnected;
};

} // namespace android

#endif // CAR_POWER_MANAGER
