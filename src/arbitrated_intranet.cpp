//
// Created by Samuel on 20/02/2024.
//

#include "arbitrated_intranet.hpp"

bool ArbitratedIntranet::read() {
	if(!isReadAvailable())
		return false;

	volatile uint8_t dataIn = readByte();
	switch (status) {
		case DEST:
			// Checking if the packet is destined to us
			if(dataIn == _self) {
				status = SRC;
				_msg.dest = _self;
			}
			// If not, wait for next packet
			break;
		case SRC:
			// Registering the source
			_msg.src = dataIn;

			// Resetting the packet ID and payload
			_msg.id = 0x00;
			for (uint8_t& elem : _msg.data)
				elem = 0x00;

			status = ID;
			break;
		case ID:
			// Registering the ID of the incoming packet
			_msg.id = dataIn;

			status = LEN;
			break;
		case LEN:
			// Registering the length of the incoming packet
			_msg.len = dataIn;

			// Resetting the buffer index
			parserIdx = 0;

			status = DATA;
			break;
		case DATA:
			// Registering incoming data into the buffer until specified packet length is reached
			if(parserIdx < _msg.len)
				_msg.data[parserIdx++] = dataIn;

			// Checking the packet once the payload is read
			if (parserIdx >= _msg.len)
				status = CSC;

			break;
		case CSC:
			if(checkFunction(_msg) == dataIn)
				callback();

			// Resetting parser
			status = DEST;
			break;
	}

	return true;
}

uint8_t ArbitratedIntranet::checkFunction(const ArbitratedIntranetMessage& msg) {
	uint8_t out = 0x00;

	for(uint8_t i = 0; i < msg.len; i++)
		out += msg.data[i];
	return 0;
}

bool ArbitratedIntranet::write(const ArbitratedIntranetMessage &msg) {
	if(!isWriteAvailable())
		return false;

	writeByte(msg.dest);
	writeByte(msg.src);
	writeByte(msg.id);
	writeByte(msg.len);

	for (uint8_t i = 0; i < msg.len; i++)
		writeByte(msg.data[i]);

	writeByte(checkFunction(msg));
}
