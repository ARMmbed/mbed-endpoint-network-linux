/**
 * @file    mbed.h
 * @brief   mbed.h header stubs for Linux
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

#ifndef __MBED_H__
#define __MBED_H__

// stdio
#include <stdio.h>

// memory utils
#include <string.h>

// String class
#include <string>
using namespace std;

// Serial stub
#include "mbed-drivers/Serial.h"

// Thread stub
#include "mbed-drivers/Thread.h"

#endif // __MBED_H__
