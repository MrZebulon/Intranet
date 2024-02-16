//
// Created by Samuel on 16/02/2024.
//

#ifndef INTRANET_INTRANET_WORKER_HPP
#define INTRANET_INTRANET_WORKER_HPP

#include <cstdint>

class IntranetWorker {
public:
	IntranetWorker(uint8_t idIn, uint8_t statusIn) : id(idIn), status(statusIn) {}

	virtual void reset() = 0;
	virtual bool tick(uint8_t* payload, uint32_t len) = 0;
protected:
	uint8_t id;
	uint8_t status;
};


#endif //INTRANET_INTRANET_WORKER_HPP
