#include "stdafx.h"
#include "Harddrive.hpp"

Harddrive::Harddrive(bool location)
{
	isInternal = location;
}

Harddrive::Harddrive()
{
}

Folder* Harddrive::access(string folder)
{
	return &folders[folder];
}

void Harddrive::Install(Software* installation, string folder, Computer* set_installedOn)
{
	folders[folder].add(installation, installation->getName(), set_installedOn);
	cout << "Successfully Installed " << installation->getName() << " in " << folder << endl;
}

void Harddrive::setState(bool set_state)
{
	isInternal = set_state;
}

void Harddrive::getState()
{
	if (isInternal)
	{
		cout << "Internal Drive" << endl;
	}
	else
	{
		cout << "External Drive" << endl;
	}
}

Software* Harddrive::open(string folder, string name)
{
	return folders[folder].open(name);
}

void Harddrive::close(string folder, string name)
{
	folders[folder].close(name);
}

void Harddrive::setID(string set_ID)
{
	ID = set_ID;
}

void Harddrive::getID()
{
	cout << "The ID of this drive is: " << ID << endl;
}

int Harddrive::getFolders()
{
	return folders.size();
}

void Harddrive::addFolder(string name)
{
	Folder new_folder;
	new_folder.set_name(name);
	folders.insert(std::pair<string, Folder>(name, new_folder));
}
