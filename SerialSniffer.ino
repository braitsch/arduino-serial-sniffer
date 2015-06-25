
#include "SerialSniffer.h"

SerialSniffer sniffer;

// sample commands/opcodes
#define NUM_COMMANDS 4
typedef enum {
	START = 11,
	STOP = 10,
	PRINT = 4,
	DELETE = 2
};
int commands[NUM_COMMANDS] = {START, STOP, PRINT, DELETE};

void setup() 
{
	sniffer.begin(19200);
	sniffer.onDataReceived(&parseSerialData);
}

void loop() 
{	
	sniffer.listen();
}

void parseSerialData(int cmd)
{
// check if we got a command we care about //
	for(size_t i = 0; i < NUM_COMMANDS; ++i)
	{
		if (commands[i] == cmd){
			Serial.print("command        : "); Serial.println(cmd);
			Serial.print("payload length : "); Serial.println(sniffer.getPayloadLength());
			char* pChar = sniffer.getPayload();
			Serial.print("payload char   : "); Serial.println(pChar);
			String pString = sniffer.getPayloadString();
			Serial.print("payload string : "); Serial.println(pString);
		}
	}
}
