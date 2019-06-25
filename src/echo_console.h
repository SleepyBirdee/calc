#ifndef __ECHO_CONSOLE_H
#define __ECHO_CONSOLE_H

#include <syslog.h>     /* LOG_* */
#include <errno.h>

#define DEBUG_LEVEL LOG_DEBUG

#define ECHO_CONSOLE_DEBUG(fmt, args...) do {\
    if (DEBUG_LEVEL >= LOG_DEBUG) \
        echo_console(LOG_DEBUG, "[%s:%d]: " fmt "", __func__, __LINE__, ## args);\
} while (0)

#define ECHO_CONSOLE_INFO(fmt, args...) do {\
    if (DEBUG_LEVEL >= LOG_INFO)\
        echo_console(LOG_INFO, "[%s:%d]: " fmt "", __func__, __LINE__, ## args);\
} while (0)
    
#define ECHO_CONSOLE_ERR(fmt, args...) do {\
    if (DEBUG_LEVEL >= LOG_ERR)\
        echo_console(LOG_ERR, "[%s:%d]: " fmt "", __func__, __LINE__, ## args);\
} while (0)

extern void echo_console(int level, const char *fmt, ...);

#endif /* echo_console.h */ 
