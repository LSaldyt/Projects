#include "stdafx.h"

#ifndef USER_HPP
#define USER_HPP

#include "Permissions.hpp"

class User
{
private:
	string password; //Since we aren't going to do anything with hashes, why not have the user class store the password, kindof like how google does..
	//Don't want any derived classes taking your password!
protected:
	string name;
	Permissions perm_level; //not the haircut Or is it

public:
	User();

	string User::generateRandomName();

	void login(string username, string password); //Added these for you only because Operating System has to make calls to them.
	void logout(); //They aren't actually defined yet, as Visual studio will probably tell you

	string getName();
};

#endif