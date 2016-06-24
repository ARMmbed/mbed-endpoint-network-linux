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
