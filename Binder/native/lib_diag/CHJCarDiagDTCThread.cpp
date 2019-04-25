#include "CHJCarDiagDTCThread.h"

namespace android
{
    CHJCarDiagDTCThread::CHJCarDiagDTCThread(const sp < CHJCarDiagDTCMonitor > & monitor):
    Thread( true ),mCHJCarDiagMonitor( monitor )
    {
    }

    CHJCarDiagDTCThread::~CHJCarDiagDTCThread()
    {
    }

    bool CHJCarDiagDTCThread::threadLoop()
    {
        mCHJCarDiagMonitor->loopMonitor();
        return true;
    }
}
