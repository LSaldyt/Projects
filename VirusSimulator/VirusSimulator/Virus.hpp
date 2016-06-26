#include "stdafx.h"
#include "Software.hpp"

#ifndef VIRUS_HPP
#define VIRUS_HPP

class Virus : public Software
{
private:
	string name;
	string version;
	int ipGatherLimit = 10000;

public:
	Virus& Virus::operator=(const Virus& cSource);
	Virus* copy(); //This is extremely useful, as well as polymorphic. Make sure to use this instead of the assignment operator, even though it's been overloaded

	void spreadUSB();
	void spreadNetwork();//These two functions don't exist on the software object, but they get called by open(), which is an override of a virutal function in the Software object

	Software* open();
	//Open function is overridden to call spread() functions

	Virus();
	Virus(string, string);
	~Virus();
};

#endif
