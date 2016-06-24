/**
 * @file    Serial.h
 * @brief   Serial stubs for Linux
 * @author  Doug Anson
 * @version 1.0
 * @see
 *
 * Copyright (c) 2014
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

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
