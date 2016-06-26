#include "stdafx.h"
#include "Software.hpp"
#include "Computer.hpp"

Software* Software::copy()
{
	Software* copy = new Software();
	*copy = *this;
	return copy;
}

Software* Software::open()
{
	//Create a new instance of a piece of software
	isOpen = true;
	instances.push_back(Instance());
	return this;
}

void Software::close()
{
	isOpen = false;
	if (instances.size() > 0) 
	{
		instances.erase(instances.end() - 1);
	}
}

string Software::getName()
{
	return name;
}

void Software::setName(string set_name)
{
	name = set_name;
}

void Software::setVersion(string set_version)
{
	version = set_version;
}

string Software::getVersion()
{
	return version;
}

Software::Software() 
{
	installedOn = NULL;
	instances.clear();
	isOpen = false;
	name = "unnamed";
	version = "";
}

Software::Software(string set_name, string set_version)
{
	instances.clear();
	isOpen = false;
	name = set_name;
	version = set_version;
}

void Software::printInstances()
{
	if (isOpen)
	{
		cout << "The software is open" << endl;
	}
	else
	{
		cout << "The software is closed" << endl;
	}
	cout << instances.size() << " Instances open" << endl;
}

void Software::setInstalledOn(Computer* set_installedOn)
{
	installedOn = set_installedOn;
}

Instance Software::access(int ID)
{
	return instances[ID];
}

Instance::Instance()
{
	ID = 0;
}

Instance::Instance(int set_ID)
{
	ID = set_ID;
}

int Instance::getID()
{
	return ID;
}

Software& Software::operator=(const Software& cSource)
{
	name = cSource.name;
	instances.clear();
	isOpen = false;
	version = cSource.version;
	perm_level = cSource.perm_level;
	installedOn = NULL;

	return *this;
}