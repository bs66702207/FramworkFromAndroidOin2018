#ifndef __CHJ_DIAG_COMM_BASE_H__
#define __CHJ_DIAG_COMM_BASE_H__

#include "CHJCarDiagNativeParam.h"


namespace android
{


class CHJDiagCommBase : public virtual RefBase
{
public:
    virtual ~CHJDiagCommBase() = default;

    /**
     * Closes a connection if it is open.
     */
    virtual void stop() {}

    /**
     * Creates a connection to the other side.
     *
     * @return int Returns fd or socket number if connection is successful.
     *              Otherwise, returns -1 if no connection is availble.
     */
    virtual int connect() { return 0; }

    
    /**
     * Opens the communications channel.
     *
     * @return int Returns 0 if channel is opened, else -errno if failed.
     */
    virtual int open() = 0;

    virtual String8 read() = 0;
    
    virtual int getSocketFd()=0;

    virtual int write( String8 msg )=0;
 };
}
#endif /*__CHJ_DIAG_COMM_BASE_H__*/
