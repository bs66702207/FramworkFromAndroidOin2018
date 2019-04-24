#include "debug.h"
 
/*
 * define the debug level of this file,
 * please see 'debug.h' for detail info
 */
DEBUG_SET_LEVEL(DEBUG_LEVEL_DEBUG);
 
int main(void) {
    ERR("This is a error message\n");
    INFO("This is a info message\n");
    DEBUG("This is a debug message\n");
 
    ASSERT();
    return 0;
}
