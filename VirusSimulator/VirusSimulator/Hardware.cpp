#include "stdafx.h"
#include "Hardware.hpp"

Hardware::Hardware()
{
	model = "";
}

Hardware::Hardware(string set_model)
{
	model = set_model;
}

void Hardware::setModel(string set_model)
{
	model = set_model;
}

string Hardware::getModel()
{
	return model;
}

void Hardware::set_installedOn(Computer* set_installedOn)
{
	installedOn = set_installedOn;
}

class Computer;

Computer* Hardware::get_installedOn()
{
	return installedOn;
}