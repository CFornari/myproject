#ifndef __UDP_H__
#define __UDP_H__

#include "global_core.h"

void onReceive(UdpConnection& connection, char* data, int size, IPAddress remoteIP, uint16_t remotePort);

void gotIP(IPAddress ip, IPAddress gateway, IPAddress netmask);

extern UdpConnection _udp; 

#endif