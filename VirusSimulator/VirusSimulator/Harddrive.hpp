#include "stdafx.h"

#ifndef HARDDRIVE_HPP
#define HARDDRIVE_HPP

#include "StorageDevice.hpp"
#include "Folder.hpp"

class Harddrive : public StorageDevice
{
protected:
	bool isInternal;
	string ID;
	unordered_map<string, Folder> folders;

public:
	Harddrive();
	~Harddrive() {}

	Harddrive(bool);

	Folder* access(string);
	void Install(Software*, string, Computer*);
	//This makes a copy at the folder level, so make sure not to change to software pointer at this level, otherwise it will corrupt the source

	void setState(bool);
	void getState();
	 
	Software* open(string, string);
	void close(string, string);

	int getFolders();
	void addFolder();
	void setID(string);
	void getID();

	void addFolder(string name);
};

#endif

