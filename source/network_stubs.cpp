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

// Linux Includes
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h> /* For SIGIGN and SIGINT */

// mbed Includes
#include "mbed-endpoint-network/mbedEndpointNetworkStubs.h"

// Logger
#include "mbed-connector-interface/Logger.h"
extern Logger logger;

// endpoint pointer
static void *_my_endpoint = NULL;

extern "C" {

// forward reference of main() entry point
extern void app_start(int argc,char *argv[]);

pthread_t unregister_thread;
pthread_t observation_thread;
pthread_t update_register_thread;
volatile bool loop;

typedef void (*signalhandler_t)(int); /* Function pointer type for ctrl-c */

// Linux Handlers
static void ctrl_c_handle_function(void) {
    if (_my_endpoint != NULL) {
        Connector::Endpoint *ep = (Connector::Endpoint *)_my_endpoint;
        ep->de_register_endpoint();
    }
    exit(1);
}

void* wait_for_unregister(void* arg) {
     Connector::Endpoint *ep = (Connector::Endpoint *)arg;
     if(ep->isRegistered() == false) {
         printf("Unregistered done\n");
         pthread_detach(update_register_thread);
         pthread_detach(observation_thread);
         pthread_detach(unregister_thread);
         loop = false; 
         pthread_cancel(update_register_thread);
         pthread_cancel(observation_thread);
        pthread_cancel(unregister_thread);
     }
    return NULL;
}

void *update_registration(void* arg) {
    Connector::Endpoint *ep = (Connector::Endpoint *)arg;
    while(1) {
        sleep(30);
        ep->re_register_endpoint();
    }
    return NULL;
}


void *register_endpoint(void *arg) {
    Connector::Endpoint *ep = (Connector::Endpoint *)arg;
    if (ep->isRegistered() == false) {
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
    pthread_create(&observation_thread, NULL, &register_endpoint,(void *)endpoint);
}

// create a suitable main event loop for this specific network
void net_create_main_loop(Connector::Endpoint * /*endpoint */)
{
     // nothing to create - create and dispatch will occur in begin_main_loop() below
     ;
}

// begin the main loop for processing network events
void net_begin_main_loop(Connector::Endpoint *endpoint)
{
    // Initialize our main loop...
    logger.log("mbedEndpointNetwork(Linux): Starting main loop...");
    pthread_create(&update_register_thread,NULL,&update_registration,(void *)endpoint);
    pthread_create(&unregister_thread,NULL,&wait_for_unregister,(void*)endpoint);

    // enter main loop
    while(loop);
}

// setup shutdown button
void net_setup_deregistration_button(void *p) {
    // set signal handler for ctrl-c
    signal(SIGINT, (signalhandler_t)ctrl_c_handle_function);
}

// main()
int main(int argc,char *argv[]) {
    app_start(argc,argv);	
}
