#include "stdafx.h"

#ifndef HARDWARE_HPP
#define HARDWARE_HPP
class Computer;

class Hardware
{
protected:
	string model;
	Computer* installedOn;

public:
	Hardware();
	Hardware(string);
	~Hardware() {};

	void setModel(string);
	string getModel();

	virtual void set_installedOn(Computer*);
	Computer* get_installedOn();
};

#endif
