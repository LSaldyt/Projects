#include "stdafx.h"

#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "Software.hpp"

class Folder
{
protected:
	string name;
	unordered_map<string, Software*> software_ptrs;

public:

	Software* open(string);
	void close(string);
	void printInstances(string);
	void openAll(Computer*); //Used for autorun()

	void add(Software*, string, Computer*);

	void set_name(string);
	string get_name();

	Software* getSoftware(string);
};


#endif
