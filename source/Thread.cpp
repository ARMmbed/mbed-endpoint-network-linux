/**
 * @file    Thread.cpp
 * @brief   Thread implementation for Linux
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

// ThreadedResourceObserver support
#include "mbed-connector-interface/ThreadedResourceObserver.h"

// our Thread instance pointer...
void *_thread_instance = NULL;

// we simply call the _observation_notifier() from ThreadedResourceObserver...
void *_thread_cb_fn(void *arg) {
     Thread *thr = (Thread *)_thread_instance;
     if (thr != NULL) {
	ThreadedResourceObserver::_observation_notifier((void const *)thr->getInstance());
     }
     return NULL;
}
