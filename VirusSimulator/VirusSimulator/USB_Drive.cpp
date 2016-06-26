#include "stdafx.h"
#include "USB_Drive.hpp"

USB_Drive::USB_Drive()
{
	ID = 0;
	beingUsed = false;
	folders.insert(std::pair<string, Folder>("default", Folder()));
	//"default" folder refers to the Drive itself, similar to the concept of a desktop
}

USB_Drive::USB_Drive(int set_space,  string set_model)
{
	space = set_space;
	model = set_model;

	ID = 0;
	beingUsed = false;
	folders.insert(std::pair<string, Folder>("default", Folder()));
	//"default" folder refers to the Drive itself, similar to the concept of a desktop
}

void USB_Drive::setID(int set_ID)
{
	ID = set_ID;
}

int USB_Drive::getID()
{
	return ID;
}

void USB_Drive::open(string folder, string name)
{
	folders[folder].open(name);
}

void USB_Drive::close(string folder, string name)
{
	folders[folder].close(name);
}

void USB_Drive::autorun()
{
	std::vector<string> keys;
	keys.reserve(folders.size());
	//Extract keys from the list of folders, then use them to open software in the folders

	for (auto kv : folders) {
		keys.push_back(kv.first);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		folders[keys[i]].openAll(installedOn);
	}

	cout << "Opening all executables in all folders on " << model << endl;
}

void USB_Drive::Install(Software* installation, string folder, Computer* set_installedOn)
{
	folders[folder].add(installation, installation->getName(), set_installedOn);
}

void USB_Drive::setInstalledOn(Computer* set_installedOn)
{
	installedOn = set_installedOn;
}