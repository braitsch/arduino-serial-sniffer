Arduino Serial Sniffer
---

> A simple class to parse incoming serial data into an opcode & payload.<br>Take a look at SerialSniffer.ino for a more detailed example of how to use it.

Basic Usage
---

	#include "SerialSniffer.h"
	
	SerialSniffer sniffer;
	
	void setup() 
	{
	// tell the sniffer to listen at 19200 baud //
		sniffer.begin(19200);
	// register a callback to be executed when incoming serial data is received //
		sniffer.onDataReceived(&parseSerialData);
	}
	
	void loop() 
	{
		sniffer.listen();
	}
	
	void parseSerialData(int cmd)
	{
		Serial.print("command        : "); Serial.println(cmd);
		Serial.print("payload length : "); Serial.println(sniffer.getPayloadLength());
		char* pChar = sniffer.getPayload();
		Serial.print("payload char   : "); Serial.println(pChar);
		String pString = sniffer.getPayloadString();
		Serial.print("payload string : "); Serial.println(pString);
	}

Serial Monitor
---

> Open the Serial Monitor and enter an integer (opcode) and string (payload) separated by a forward slash such as: <b>76/braitsch</b>

Considerations
---
> This is very much a wip and will continue to evolve. Feedback / questions are welcome.
