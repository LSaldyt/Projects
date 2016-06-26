#include "stdafx.h"

#ifndef STORAGEDEVICE_HPP
#define STORAGEDEVICE_HPP

#include "Hardware.hpp"
#include "Software.hpp"

class StorageDevice : public Hardware
{
protected:
	int space;

public:
	void setSpace(int);
	void getSpace();

};

#endif


