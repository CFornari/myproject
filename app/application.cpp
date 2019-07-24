#include "global_core.h"
#include "m_udp.h"

void init()
{
	// Set clock frequency to 160MHz.
	SystemClass sys;
	sys.setCpuFrequency(CpuFrequency::eCF_160MHz);
	if (sys.getCpuFrequency() == CpuFrequency::eCF_80MHz)
		Serial.printf(_F("Running at 80MHz\n"));
	else
		Serial.printf(_F("Running at 160MHz\n"));

	// Configure and init the GPIO's.
	pinMode(NX_COL, OUTPUT);
	pinMode(RT_COL, OUTPUT);
	pinMode(NX_ROW, OUTPUT);
	pinMode(RT_ROW, OUTPUT);
	digitalWrite(NX_COL, false);
	digitalWrite(RT_COL, false);
	digitalWrite(NX_ROW, false);
	digitalWrite(RT_ROW, false);

	Serial.begin(115200); // 115200 by default
	Serial.systemDebugOutput(true);

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiEvents.onStationGotIP(gotIP);
}