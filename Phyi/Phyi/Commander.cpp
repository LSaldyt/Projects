#include "Commander.hpp"



Commander::Commander()
{
}

Commander::~Commander()
{
}

void Commander::add(std::string s, ShipTemplate t)
{
	templates.insert(std::make_pair(s, t));
}

std::unordered_map<std::string, ShipTemplate>* Commander::getTemplates()
{
	return &templates;
}
