#include "stdafx.h"

#ifndef BROWSER_HPP
#define BROWSER_HPP

#include "Software.hpp"

class Website;

class Browser : public Software
{
private:
	static unordered_map<string, Website*> theEntireInternet;
	Website* currentWebsite;

public:
	Browser();
	Browser(string, string);
	~Browser();

	static void addSite(Website*);
	static void removeSite(Website*);

	void goTo(string); //Distinction  from the statement 'goto':P
	void search();

	void download(string);

};

#endif