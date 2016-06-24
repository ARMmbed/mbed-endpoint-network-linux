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

// Includes...
#include "mbed-endpoint-network/mbedEndpointNetworkStubs.h"

// Logger
#include "mbed-connector-interface/Logger.h"
extern Logger logger;

// endpoint pointer
static void *_my_endpoint = NULL;

extern "C" {

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
   	mbed::util::FunctionPointer2<void, M2MSecurity*, M2MObjectList> fp(endpoint, &Connector::Endpoint::register_endpoint);
        minar::Scheduler::postCallback(fp.bind(endpoint->getEndpointSecurity(),endpoint->getEndpointObjectList()));
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
    Connector::Options *options = endpoint->getOptions();
    minar::Scheduler::postCallback(endpoint,&Connector::Endpoint::re_register_endpoint).period(minar::milliseconds(options->getRegUpdatePeriod()));
}

// setup shutdown button
void net_setup_deregistration_button(void *p) {
}

}
