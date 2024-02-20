//
// Created by Samuel on 20/02/2024.
//

#ifndef INTRANET_ARBITRATED_INTRANET_HPP
#define INTRANET_ARBITRATED_INTRANET_HPP

#include <cstdint>
#include "intranet.hpp"

#define MAX_DATA_LEN_BYTES 8
#define METADATA_BYTES 5
enum ArbitrationStatus {
	DEST,
	SRC,
	ID,
	LEN,
	DATA,
	CSC
};

struct ArbitratedIntranetMessage {
	uint8_t dest;
	uint8_t src;
	uint8_t id;
	uint8_t len;
	uint8_t data[8];
	uint8_t csc;
};

class ArbitratedIntranet : public virtual Intranet<ArbitratedIntranetMessage> {
public:
	ArbitratedIntranet(uint8_t self) : _self(self) {}
	bool read() override;
	bool write(const ArbitratedIntranetMessage& msg) override;
protected:
	uint8_t _self;
	ArbitrationStatus status;
	uint8_t parserIdx;

	virtual void callback() = 0;
	virtual uint8_t readByte() = 0;
	virtual void writeByte(const uint8_t& byte) = 0;
	virtual bool isReadAvailable() = 0;
	virtual bool isWriteAvailable() = 0;
	virtual uint8_t checkFunction(const ArbitratedIntranetMessage& msg);
};

#endif //INTRANET_ARBITRATED_INTRANET_HPP
