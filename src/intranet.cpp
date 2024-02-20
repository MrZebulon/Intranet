//
// Created by Samuel on 16/02/2024.
//

#include "intranet.hpp"

bool Intranet::decode() {
	if(!available())
		return false;

	uint8_t dataIn = readByte();
	switch (status) {
		case PACKET_DEST:
			// Checking if the packet is destined to us
			if(dataIn == self)
				status = PACKET_SRC;

			// If not, wait for next packet
			break;
		case PACKET_SRC:
			// Registering the source
			packetSrc = dataIn;

			// Resetting the packet ID and payload
			packetId = 0x00;
			for (uint8_t& elem : buffer)
				elem = 0x00;

			status = PACKET_ID;
			break;
		case PACKET_ID:
			// Registering the ID of the incoming packet
			packetId = dataIn;

			status = PACKET_LENGTH;
			break;
		case PACKET_LENGTH:
			// Registering the length of the incoming packet
			packetLen = dataIn;

			// Resetting the buffer index
			packetIdx = 0;

			status = PACKET_PAYLOAD;
			break;
		case PACKET_PAYLOAD:
			// Registering incoming data into the buffer until specified packet length is reached
			if(packetIdx < packetLen)
				buffer[packetIdx++] = dataIn;

			// Checking the packet once the payload is read
			if (packetIdx >= packetLen)
				status = PACKET_CHECK;

			break;
		case PACKET_CHECK:
			if(checkFunction(buffer, packetLen) == dataIn)
				callback();

			// Resetting parser
			status = PACKET_DEST;
			break;
	}

	return true;
}

void Intranet::encode(uint8_t packetDestIn, uint8_t idIn, uint8_t* payloadIn, uint8_t lenIn) {
	writeByte(packetDestIn);
	writeByte(self);
	writeByte(idIn);
	writeByte(lenIn);

	for (uint8_t i = 0; i < lenIn; i++)
		writeByte(payloadIn[i]);

	writeByte(checkFunction(payloadIn, lenIn));
}

uint8_t Intranet::checkFunction(uint8_t* bufferIn, uint8_t lenIn) {
	// Default check = checksum
	uint8_t out = 0x00;

	for(uint8_t i = 0; i < lenIn; i++)
		out += bufferIn[i];

	return out;
}
