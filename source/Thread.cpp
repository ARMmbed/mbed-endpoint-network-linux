#include "mbed-connector-interface/ThreadedResourceObserver.h"

void *_thread_instance = NULL;
void *_thread_cb_fn(void *arg) {
     Thread *thr = (Thread *)_thread_instance;
     if (thr != NULL) {
	ThreadedResourceObserver::_observation_notifier((void const *)thr->getInstance());
     }
     return NULL;
}
