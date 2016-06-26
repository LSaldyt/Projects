#include "stdafx.h"

#ifndef USBHUB_HPP
#define USBHUB_HPP

#include "Hardware.hpp"
#include "USB_Drive.hpp"

class USB_slot
{
protected:
	bool enabled;
	bool empty;
	USB_Drive *p_drive;
	int ID;

public:
	void enable();
	void disable();
	void checkEnabled();

	void set_ID(int set_ID) { ID = set_ID; }
	int get_ID() { return ID; }

	bool isEmpty();
	void setEmpty(bool set) { empty = set; }
	void insert(USB_Drive*, Computer*);
	void eject(USB_Drive*, int);
	USB_Drive* accessDrive();

	void Install(Software*, string, Computer*);
};



class USB_hub : public Hardware
{
protected:
	vector<USB_slot> slots;
	Computer* installedOn;

public:

	void enableAll();
	void disableAll();
	void checkAll();

	void insert(USB_Drive*, Computer*);
	void eject(USB_Drive*, int);
	int getEmptySlot();
	int getFullSlots();
	vector<USB_slot>* accessSlots();
	USB_Drive* getLatest();

	USB_hub(int, Computer*);
	USB_hub() {};
	~USB_hub() {}
};

#endif
