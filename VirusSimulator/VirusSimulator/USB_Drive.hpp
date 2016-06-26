#include "stdafx.h"

#ifndef USB_DRIVE_HPP
#define USB_DRIVE_HPP

#include "StorageDevice.hpp"
#include "Folder.hpp"

class USB_Drive : public StorageDevice
{
protected:
	unordered_map<string, Folder> folders;
	int ID;
	bool beingUsed;
	Computer* installedOn; //Refers to the computer housing it

public:
	void setID(int set_ID);
	int getID();

	void open(string, string);
	void close(string, string);
	void autorun();

	void setState(bool set_state) { beingUsed = set_state; }
	bool checkState() { return beingUsed; }

	void Install(Software*, string, Computer*);

	void setInstalledOn(Computer*);

	USB_Drive();
	USB_Drive(int, string);
	~USB_Drive() {};
};

#endif

