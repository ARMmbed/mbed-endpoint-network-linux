/**
 * @file    Thread.h
 * @brief   Thread header stubs for Linux
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

#ifndef __THREAD_H__
#define __THREAD_H__

// Linux Includes
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// dispatch function signature
typedef void (* dispatch_fn)(const void* arg);

// forward references
extern void *_thread_cb_fn(void *arg);
extern void *_thread_instance;

class Thread {
    public:
	Thread(dispatch_fn fn,void *instance) {
	   this->m_fn = fn;
           this->m_instance = instance;
	   _thread_instance = (void *)this;
           pthread_create(&this->m_thread,NULL,_thread_cb_fn,this);
	}

	~Thread() {
	   this->terminate();
	}

        void terminate() {
           pthread_detach(this->m_thread);
	   pthread_cancel(this->m_thread);
        }

	static void wait(int time_ms) {
	   int time_s = (int)(time_ms/1000);
	   sleep(time_s);
	}
	
	void *getInstance() { 
	    return this->m_instance;
	}


    private:
 	dispatch_fn m_fn;
	void       *m_instance;
        pthread_t   m_thread;
	
};

#endif // __THREAD_H__
