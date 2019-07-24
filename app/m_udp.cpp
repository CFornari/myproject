#include "m_udp.h"

UdpConnection _udp(onReceive); // Declaration of global var.

void onReceive(UdpConnection& connection, char* data, int size, IPAddress remoteIP, uint16_t remotePort)
{
	// debugf("UDP Sever callback from %s:%d, %d bytes", remoteIP.toString().c_str(), remotePort, size);

	// // We implement string mode server for example
	// Serial.print(">\t");
	// Serial.print(data);
	// Serial.println();

	// // Send echo to remote sender
	// String text = String("echo: ") + data;
	// _udp.sendStringTo(remoteIP, remotePort, text);
	switch (*data)
	{
	case 's': // Read single 
		Serial.println(_F("Starting..."));

		break;
	
	default:

		break;
	}
}

void gotIP(IPAddress ip, IPAddress gateway, IPAddress netmask)
{
	_udp.listen(UDP_PORT);
	Serial.println(_F("\r\n=== UDP SERVER STARTED ==="));
	Serial.print(ip.toString());
	Serial.print(_F(":"));
	Serial.println(UDP_PORT);
	Serial.println(_F("=============================\r\n"));
}