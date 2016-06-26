#include "stdafx.h"

#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include "Connection.hpp"
class Software;

class Website
{
private:
	string url;
	unordered_map<string, Software*> downloads;

	static int URL_ID;

public:

	string getURL();
	Software* download(string);

	void upload(Software*);

	Website();
	Website(string);
	~Website();

};

#endif
