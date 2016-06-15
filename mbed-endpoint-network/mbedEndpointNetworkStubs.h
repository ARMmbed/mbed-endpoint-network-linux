 /**
 * @file    mbedEndpointNetworkStubs.h
 * @brief   mbed Endpoint Network Stubs header - these must be implemented in any lower network layer interfacing with mbedConnectorInterface
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
 
 #ifndef __MBED_ENDPOINT_NETWORK_STUBS_H__
 #define __MBED_ENDPOINT_NETWORK_STUBS_H__

// Connector Endpoint
#include "mbed-connector-interface/ConnectorEndpoint.h"

// Ethernet Interface with Minar Scheduling
#include "EthernetInterface.h"
#include "sockets/UDPSocket.h"

// Minar support
#include "minar/minar.h"

// IPv4 support
#include "lwipv4_init.h"
 
 // DEBUG
#ifndef NDEBUG
#define DEBUG_OUT(...) { printf(__VA_ARGS__); }
#else
#define DEBUG_OUT(...) /* nothing */
#endif
 
#endif // __MBED_ENDPOINT_NETWORK_STUBS_H__
