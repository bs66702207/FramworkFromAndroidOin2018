#ifndef __CHJ_CAR_DIAG_DTC_THREAD_H__
#define __CHJ_CAR_DIAG_DTC_THREAD_H__


#include <utils/Condition.h>
#include <utils/Thread.h>
#include <utils/Mutex.h>
#include <utils/Timers.h>
#include <utils/String8.h>
#include <utils/BitSet.h>
#include <utils/SortedVector.h>

#include <stddef.h>
#include <unistd.h>

#include "CHJCarDiagDTCMonitor.h"

/* Reads raw events from the socket and processes them, endlessly. */
namespace android
{
    class CHJCarDiagDTCThread : public Thread 
    {
    public:
        explicit CHJCarDiagDTCThread(const sp<CHJCarDiagDTCMonitor>& monitor);
        virtual ~CHJCarDiagDTCThread();
    
    private:
    
        virtual bool threadLoop();
        sp<CHJCarDiagDTCMonitor> mCHJCarDiagMonitor;
    };
}

#endif /*__CHJ_CAR_DIAG_DTC_THREAD_H__*/

