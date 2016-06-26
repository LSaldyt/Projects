#include "stdafx.h"
#include "USBHub.hpp"
#include "USB_Drive.hpp"

USB_hub::USB_hub(int set_slots=2, Computer* set_installedOn=NULL)
{
	for (int i = 0; i < set_slots; i++)
	{
		slots.push_back(USB_slot());
		slots[i].set_ID(i);
		slots[i].setEmpty(false);
	}
	installedOn = set_installedOn;
}

void USB_slot::enable()
{
	enabled = true;
}

void USB_slot::disable()
{
	enabled = false;
}

void USB_slot::checkEnabled()
{
	if (enabled)
	{
		cout << "Slot is enabled" << endl;
	}
	else
	{
		cout << "Slot is disabled" << endl;
	}
}

void USB_hub::enableAll()
{
	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].enable();
		slots[i].setEmpty(true);
	}
}

void USB_hub::disableAll()
{
	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].disable();
		slots[i].setEmpty(true);
	}
}

void USB_hub::checkAll()
{
	for (int i = 0; i < slots.size(); i++)
	{
		cout << "Slot: " << i << " ";
 		slots[i].checkEnabled();
	}
}

void USB_hub::insert(USB_Drive* drive, Computer* set_installedOn)
{
	drive->setInstalledOn(set_installedOn);
	int path = getEmptySlot();
	slots[path].insert(drive, set_installedOn);
	slots[path].setEmpty(false);
}

void USB_hub::eject(USB_Drive* drive, int ID)
{
	if (ID <= slots.size()) 
	{
		slots[ID].eject(drive, ID);
	}
	else
	{
		cout << "Invalid ID given" << endl;
	}
}

//Below are the functions for the individual slots, above are the functions for the hub

void USB_slot::insert(USB_Drive* drive, Computer* set_installedOn)
{
	if (!drive->checkState()) {
		p_drive = drive;
		p_drive->setID(ID);
		p_drive->setState(true);
		p_drive->setInstalledOn(set_installedOn);
	}
	else
	{
		cout << "Drive already in use" << endl;
	}
}

void USB_slot::eject(USB_Drive* drive, int ID)
{
	p_drive = NULL;
	drive->setState(false);
}

bool USB_slot::isEmpty()
{
	return empty;
}

int USB_hub::getEmptySlot()
{
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots[i].isEmpty()) 
		{
			return i;
		}
	}
	cout << "No empty USB slots were found. Unable to plug in device." << endl;
}


int USB_hub::getFullSlots()
{
	int i = 0;
	while (!slots[i].isEmpty()){
		i++;
	}
	return i;
}

vector<USB_slot> * USB_hub::accessSlots()
{
	return &slots;
}

void USB_slot::Install(Software* installation, string folder, Computer* set_installedOn)
{
	if (!isEmpty())
	{
		p_drive->Install(installation, folder, set_installedOn);
	}
}

USB_Drive* USB_slot::accessDrive()
{
	return p_drive;
}

USB_Drive* USB_hub::getLatest()
{
	return slots[getEmptySlot() - 1].accessDrive();
}