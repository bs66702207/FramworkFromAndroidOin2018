#ifndef __CHJ_CAR_DIAG_COMM_THREAD_H__
#define __CHJ_CAR_DIAG_COMM_THREAD_H__


#include <utils/Condition.h>
#include <utils/Thread.h>
#include <utils/Mutex.h>
#include <utils/Timers.h>
#include <utils/String8.h>
#include <utils/BitSet.h>
#include <utils/SortedVector.h>

#include <stddef.h>
#include <unistd.h>

#include "CHJCarDiagReader.h"

/* Reads raw events from the socket and processes them, endlessly. */
namespace android
{
	class CHJCarDiagCommThread : public Thread 
	{
	public:
		explicit CHJCarDiagCommThread(const sp<CHJCarDiagReader>& reader);
		virtual ~CHJCarDiagCommThread();
	
	private:
	
		virtual bool threadLoop();
		sp<CHJCarDiagReader> mCHJCarDiagReader;
	};
}

#endif /*__CHJ_CAR_DIAG_COMM_THREAD_H__*/
