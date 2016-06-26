#include "stdafx.h"
#include "Website.hpp"
#include "Browser.hpp"

int Website::URL_ID = 1;

Website::Website()
{
	//Assign 1.com, 2.com and so on for unspecified URLS
	url = std::to_string(URL_ID) + ".com";
	URL_ID++;
}

Website::Website(string url)
{
	this->url = url;
	Browser::addSite(this);
}

Website::~Website()
{

}

string Website::getURL()
{
	return url;
}

Software* Website::download(string query)
{
	Software* new_download = downloads[query];
	if (new_download != NULL)
	{
		return new_download;
	}
	else
	{
		cout << "Invalid Query" << endl;
		return new_download; //return Anyways. This is handled in the browser definition of download
	}
}

void Website::upload(Software* new_upload)
{
	cout << new_upload->getName() << endl;
	downloads.insert(std::pair<string, Software*>(new_upload->getName(), new_upload));
}