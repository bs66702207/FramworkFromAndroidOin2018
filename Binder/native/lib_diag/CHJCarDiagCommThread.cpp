#include "CHJCarDiagCommThread.h"

namespace android
{
 CHJCarDiagCommThread::CHJCarDiagCommThread(const sp < CHJCarDiagReader > & reader):
    Thread( true ), mCHJCarDiagReader( reader )
 {
 }

 CHJCarDiagCommThread::~CHJCarDiagCommThread()
 {
 }

 bool CHJCarDiagCommThread::threadLoop()
 {
     mCHJCarDiagReader->loopReader();
     return true;
 }
    
}