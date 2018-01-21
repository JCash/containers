#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <Foundation/Foundation.h>

void Printf(const char* format, ...)
{
    va_list arg;
    va_start (arg, format);
    
    char buf[1024];
    vsnprintf(buf, sizeof(buf), format, arg);
    va_end (arg);

    NSString *string = [[NSString alloc] initWithUTF8String:buf];
    NSLog(@"%@", string);
}