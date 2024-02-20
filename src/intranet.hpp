//
// Created by Samuel on 16/02/2024.
//

#ifndef INTRANET_INTRANET_HPP
#define INTRANET_INTRANET_HPP

#define INTRANET_CLS template<typename T>

INTRANET_CLS class Intranet {
public:
	virtual void init() = 0;
	virtual bool read() = 0;
	virtual bool write(const T& msg) = 0;
protected:
	T _msg;
};


#endif //INTRANET_INTRANET_HPP
