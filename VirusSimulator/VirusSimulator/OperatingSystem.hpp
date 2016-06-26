#include "stdafx.h"

#ifndef OPERATINGSYSTEM_HPP
#define OPERATINGSYSTEM_HPP

#include "User.hpp"

class OperatingSystem
{
protected:
	string name = "OS"; // "Ubuntu", "Windows", etc..
	unordered_map<string, User> users;
	bool autorun;

public:

	//User related
	void login(string, string);
	void logout(string);
	void addUser(User, string);
	void removeUser(string);

	void setAutorun(bool set_autorun) { autorun = set_autorun; }
	bool getAutorun() { return autorun; }

	//Software related

	OperatingSystem();
	~OperatingSystem();

};

#endif