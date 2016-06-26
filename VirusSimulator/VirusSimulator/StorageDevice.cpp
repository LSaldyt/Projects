#include "stdafx.h"
#include "StorageDevice.hpp"

void StorageDevice::setSpace(int set_space)
{
	space = set_space;
}

void StorageDevice::getSpace()
{
	cout << "Total space: " << space << endl;
}

