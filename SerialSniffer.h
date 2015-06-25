

/*
	Arduino Serial Sniffer
	Author : Stephen Braitsch
	Description : Simple class to parse incoming Serial data into an opcode & payload separated by a '/' character.
	Notes : The example sketch currently uses about 4K bytes, 
		if space is at a premium delete any references to the Arduino String class to free up about another 1K of space.
*/

#include <Arduino.h>

class SerialSniffer{
	
	public:
		SerialSniffer(){};
		void begin(int baud)
		{
			Serial.begin(baud);
		}
		void onDataReceived ( void (*f)(int) )
		{
			onDataReceivedCallback = f;
		}
		char* getPayload()
		{
			return payload;
		}
		int getPayloadLength()
		{
			return payloadLength;
		}
	/* 
		adding string conversion as a convenience method 
		delete this function if space is limited on your microcontroller
	*/
		String getPayloadString()
		{
			String str = "";
			for(size_t i = 0; i < payloadLength; ++i)
			{
				str.concat(payload[i]);
			}
			return str;
		}
		void listen()
		{
		// clear the message buffer //
			for(size_t i = 0; i < MESSAGE_LENGTH; i++) message[i] = 0;
			int bytesReceived = 0;
			while(Serial.available()){
				bytesReceived = Serial.readBytesUntil(MESSAGE_TERMINATOR, message, MESSAGE_LENGTH);
			}
			if (bytesReceived > 0){
			// clear the command and payload buffer //
				command = 0;
				payloadLength = 0;
				for(size_t i = 0; i < PAYLOAD_LENGTH; i++) payload[i] = 0;

				activeState = COMMAND;
				for(size_t i = 0; i < bytesReceived; i++)
				{
					if (message[i] == '/'){
						activeState = PAYLOAD;
					}	else{
						if (activeState == COMMAND){
							command = command * 10 + message[i]-'0';
						}	else if (activeState == PAYLOAD){
							payload[payloadLength++] = message[i];
						}
					}
				}
			// tell anyone listening what command/opcode we've received // 
				onDataReceivedCallback(command);
			}
			Serial.flush();
		};
		
		
	private:
		enum readState {
			COMMAND, PAYLOAD
		} activeState;
		
		typedef void (*callback)(int);
		callback onDataReceivedCallback;
		
		int command;
		int payloadLength;
		static const char MESSAGE_TERMINATOR = '\n';
		static const int COMMAND_LENGTH = 4; 	// 4 chars for the command //
		static const int PAYLOAD_LENGTH = 18;	//18 chars for the payload //
		static const int MESSAGE_LENGTH = COMMAND_LENGTH + PAYLOAD_LENGTH;
		char message[MESSAGE_LENGTH];
		char payload[PAYLOAD_LENGTH];
};

