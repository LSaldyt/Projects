#pragma once
#include "Includes.hpp"
#include "Module.hpp"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadModules(std::string file);
	Module getModule(std::string key);

private:
	std::unordered_map<std::string, Module> module_map;

};