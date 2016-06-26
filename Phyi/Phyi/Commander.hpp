#pragma once
#include "ShipTemplate.hpp"
#include "Includes.hpp"

class Commander
{
public:
	Commander();
	~Commander();

	void add(std::string, ShipTemplate);
	std::unordered_map<std::string, ShipTemplate>* getTemplates();

protected:
	std::unordered_map<std::string, ShipTemplate> templates;
};

