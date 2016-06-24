#ifndef __SERIAL_H__
#define __SERIAL_H__o

#include <stdio.h>
#include <stdarg.h>

#define USBTX	0
#define USBRX	0

class Serial {
public:
    Serial(int tx = USBTX,int rx = USBRX) { ; }
    void baud(int rate) { ; }
    void printf(const char *format, ...) {
	va_list args;
        va_start(args,format);
        vprintf(format,args);
        va_end(args);
    }
};

#endif // __SERIAL_H__
