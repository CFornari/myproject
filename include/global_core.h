#ifndef __GLOBAL_CORE_H__
#define __GLOBAL_CORE_H__

#include <SmingCore.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
#define WIFI_SSID F("SSID") // Put you SSID and Password here
#define WIFI_PWD F("Password")
#endif

#define UDP_PORT 1234

#define MAX_COLS 28
#define MAX_ROWS 25
#define MAX_CELLS MAX_COLS*MAX_ROWS
#define NX_COL 16 // D0 = GPIO 16
#define NX_ROW 4  // D2 = GPIO 4
#define RT_COL 5  // D1 = GPIO 5
#define RT_ROW 0  // D3 = GPIO 0

#endif