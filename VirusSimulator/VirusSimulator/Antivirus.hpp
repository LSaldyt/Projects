#include "stdafx.h"
#include "Virus.hpp"

#ifndef ANTIVIRUS_HPP
#define ANTIVIRUS_HPP

class Antivirus : public Software
{
private:
	static unordered_set<Virus> database; //Assumes that this antivirus works off of a database that needs to be updated
	//We could create two different antivirus classes that had different methods of testing for viruses
public:

	Antivirus();
	~Antivirus();

};

#endif