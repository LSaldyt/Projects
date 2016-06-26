#include "stdafx.h"
#include "Software.hpp"
#include "Computer.hpp"
#include "Browser.hpp"
#include "Website.hpp"

unordered_map<string, Website*> Browser::theEntireInternet;

Browser::Browser()
{

}

Browser::Browser(string set_name, string set_version)
{
	name = set_name;
	version = set_version;
}

Browser::~Browser()
{

}

void Browser::addSite(Website* new_site)
{
	theEntireInternet.insert(std::pair<string, Website*>(new_site->getURL(), new_site));
	//I know that this isn't even close to how the internet works, but since it's just a simulation, I think this'll be okay
}

void Browser::removeSite(Website* deleted_site)
{
	theEntireInternet.erase(deleted_site->getURL());
	//interesting concept
}

void Browser::goTo(string get_url)
{
	currentWebsite = theEntireInternet.at(get_url);
}

void Browser::search()
{
	//Later implementation
}

void Browser::download(string download_name)
{
	Software* currentDownload = currentWebsite->download(download_name);
	if (currentWebsite != NULL && currentDownload != NULL)
	{
			getInstalledOn()->Install(currentDownload, "default");
	}
	else
	{
		cout << "Err";
	}
}