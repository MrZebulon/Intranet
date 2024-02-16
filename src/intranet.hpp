//
// Created by Samuel on 16/02/2024.
//

#ifndef INTRANET_INTRANET_HPP
#define INTRANET_INTRANET_HPP

#include <cstdint>

#define MAX_BUFFER_SIZE 1024

#define METADATA_BYTES 5

enum IntranetParserStatus {
	PACKET_DEST,
	PACKET_SRC,
	PACKET_ID,
	PACKET_LENGTH,
	PACKET_PAYLOAD,
	PACKET_CHECK
};

class Intranet {
public:
	bool decode();
	void encode(uint8_t packetDestIn, uint8_t idIn, uint8_t* payloadIn, uint32_t lenIn);


private:
	uint8_t packetLen;
	uint8_t packetIdx;
protected:
	uint8_t packetSrc;
	uint8_t packetId;

	IntranetParserStatus status;
	uint8_t buffer[MAX_BUFFER_SIZE];
	uint8_t self;

	virtual bool available() = 0;
	virtual uint8_t checkFunction(uint8_t* bufferIn, uint32_t lenIn);
	virtual void callback() = 0;

	virtual uint8_t readByte() = 0;
	virtual void writeByte(uint8_t& byte) = 0;

};


#endif //INTRANET_INTRANET_HPP
