#include "stdafx.h"
#include "Permissions.hpp"

#ifndef SOFTWARE_HPP
#define SOFTWARE_HPP
class Computer;

class Instance
{
protected:
	int ID;
	string state;
public:
	int getID();

	Instance();
	Instance(int);
	~Instance() {};
};

//A base class for any piece of software
class Software
{
protected:
	string name;
	vector<Instance> instances; //open instances of a certain type of software
	bool isOpen;
	string version;
	Permissions perm_level;
	Computer *installedOn;

	//Still expecting expansion!!
	//Maybe add in another class "Exploits", and have Software include a number of these...?
public:
	Software& Software::operator=(const Software& cSource);
	//Overloaded copy constructor!!!

	virtual Software* copy();

	virtual Software* open();
	virtual void close();

	void printInstances();
	Instance access(int);

	void setName(string);
	string getName();

	void setVersion(string);
	string getVersion();

	Software();
	Software(string name, string version);
	~Software() {};

	void setInstalledOn(Computer*);
	Computer* getInstalledOn() { if (installedOn != NULL) { return installedOn; } }
};

#endif

