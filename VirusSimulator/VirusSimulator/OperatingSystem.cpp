#include "stdafx.h"
#include "OperatingSystem.hpp"
#include "User.hpp"

void OperatingSystem::login(string username, string password)
{
	users[username].login(username, password);
}

void OperatingSystem::logout(string username)
{
	users[username].logout();
}

void OperatingSystem::addUser(User set_user, string username)
{
	users.insert(std::pair<string, User>(username, set_user));
}

void OperatingSystem::removeUser(string username)
{
	users.erase(username);
}

OperatingSystem::OperatingSystem()
{

}

OperatingSystem::~OperatingSystem()
{

}
