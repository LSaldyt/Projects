#include "stdafx.h"
#include "Folder.hpp"
#include "Computer.hpp"
#include "Virus.hpp"

void Folder::set_name(string set_name)
{
	name = set_name;
}

string Folder::get_name()
{
	return name;
}

void Folder::add(Software* installation, string name, Computer* set_installedOn)
{

	//Need to actually copy the piece of software...
	auto* new_install = installation->copy();
	new_install->setInstalledOn(set_installedOn);
	software_ptrs.insert(std::pair<string, Software*>(name, new_install));
}

Software* Folder::open(string name)
{
	if (software_ptrs[name] != NULL) //Could've made some sort of decorator for this, but it only needs to be on three seperate functions
	{                                   //Hopefully this is fine, but if any expansions happen I might change to a decorator instead
		return software_ptrs[name]->open();
	}
	else
	{
		cout << name << " does not hold a value" << endl;
	}
}

void Folder::close(string name)
{
	if (software_ptrs[name] != NULL)
	{
		software_ptrs[name]->close();
	}
	else
	{
		cout << name << " does not hold a value" << endl;
	}
}

void Folder::printInstances(string name)
{
	if (software_ptrs[name] != NULL)
	{
		software_ptrs[name]->printInstances();
	}
	else
	{
		cout << name << " does not hold a value" << endl;
	}
}

void Folder::openAll(Computer* set_installedOn)
{
	std::vector<string> keys;
	keys.reserve(software_ptrs.size());
	//Pretty similar to USB_Drive.autorun(), except with software in a particular folder object
	//Extracts keys from unordered map of software, then accesses all elements that each key refers to

	for (auto kv : software_ptrs) {
		keys.push_back(kv.first);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		software_ptrs[keys[i]]->setInstalledOn(set_installedOn); //Tell the programs about the fancy computer they've just been introduced to
		software_ptrs[keys[i]]->open();
	}
}

Software* Folder::getSoftware(string query)
{
	return software_ptrs.at(query);
}