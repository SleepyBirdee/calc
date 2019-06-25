#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "echo_console.h"

#define _LOG_MSG_LEN 256

void echo_console(int level, const char *fmt, ...){
    char buf[_LOG_MSG_LEN +32];
    char msg[_LOG_MSG_LEN];
    va_list args;
    
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);
    
    snprintf(buf, sizeof(buf), "echo \"%s\" > /dev/console \r\n", msg);
    system(buf);
} /* echo_console */