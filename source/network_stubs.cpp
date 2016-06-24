/**
 * @file    network_stubs.cpp
 * @brief   mbed Endpoint network stubs implementation (Linux)
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

// mbed Includes
#include "mbed-endpoint-network/mbedEndpointNetworkStubs.h"

// SIGNAL support
#include <signal.h> /* For SIGIGN and SIGINT */

// Logger
extern Logger logger;

// endpoint instance
static void *_my_endpoint = NULL;

// forward reference of main() entry point
extern void app_start(int argc,char *argv[]);

extern "C" {

pthread_t unregister_thread;
pthread_t observation_thread;
pthread_t update_register_thread;

// main loop
volatile bool loop = true;

typedef void (*signalhandler_t)(int); /* Function pointer type for ctrl-c */

// Linux Handlers
static void ctrl_c_handle_function(void) {
    if (_my_endpoint != NULL) {
        Connector::Endpoint *ep = (Connector::Endpoint *)_my_endpoint;
        ep->de_register_endpoint();
    }
    exit(1);
}

// wait for deregistratino to occur
void* wait_for_unregister(void* arg) {
     sleep(30);
     Connector::Endpoint *ep = (Connector::Endpoint *)arg;
     while(ep->isRegistered() == true) {
	sleep(5);
     }
     logger.log("De-registration completed. Killing Threads...");
     pthread_detach(update_register_thread);
     pthread_detach(observation_thread);
     pthread_detach(unregister_thread);
     pthread_cancel(update_register_thread);
     pthread_cancel(observation_thread);
     pthread_cancel(unregister_thread);
     loop = false; 
     return NULL;
}

void *update_registration(void* arg) {
    sleep(30);
    Connector::Endpoint *ep = (Connector::Endpoint *)arg;
    while(loop) {
        sleep(30);
        ep->re_register_endpoint();
    }
    return NULL;
}


void *register_endpoint(void *arg) {
    Connector::Endpoint *ep = (Connector::Endpoint *)arg;
    if (ep != NULL) {
	logger.log("mbedEndpointNetwork(Linux): registering endpoint...");
        ep->register_endpoint(ep->getEndpointSecurity(),ep->getEndpointObjectList());
    }
}

// plumb out the network
void net_plumb_network(void *p)   {
    // save 
    _my_endpoint = p;

    // connected
    if (p != NULL) {
	Connector::Endpoint *ep = (Connector::Endpoint *)p;
	ep->isConnected(true);
    }
}

// perform the endpoint registration
void net_perform_endpoint_registration(Connector::Endpoint *endpoint) 
{
    // register the endpoint
    logger.log("mbedEndpointNetwork(Linux): endpoint creating registration thread...");
    pthread_create(&observation_thread,NULL,&register_endpoint,(void *)endpoint);
}

// create a suitable main event loop for this specific network
void net_create_main_loop(Connector::Endpoint *endpoint)
{
     // create the registration update thread...
     logger.log("mbedEndpointNetwork(Linux): endpoint creating re-registration thread...");
     pthread_create(&update_register_thread,NULL,&update_registration,(void *)endpoint);

     // create the unregistration thread...
     logger.log("mbedEndpointNetwork(Linux): endpoint creating de-registration thread...");
     pthread_create(&unregister_thread,NULL,&wait_for_unregister,(void*)endpoint);
}

// begin the main loop for processing network events
void net_begin_main_loop(Connector::Endpoint *endpoint)
{
    // Initialize our main loop...
    logger.log("mbedEndpointNetwork(Linux): Setting CTRL-C handler...");

    // set signal handler for ctrl-c
    signal(SIGINT,(signalhandler_t)ctrl_c_handle_function);

    // enter main loop
    logger.log("mbedEndpointNetwork(Linux): endpoint starting main loop...");
    while(loop) {
	sleep(5);
    }
    logger.log("mbedEndpointNetwork(Linux): endpoint exiting...");
    exit(0);
}

// setup shutdown button
void net_setup_deregistration_button(void *p) {
}

// main()
int main(int argc,char *argv[]) {
    app_start(argc,argv);	
}

void NVIC_SystemReset() {
}

}
