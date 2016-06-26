#include "ResourceManager.hpp"
#include "CSV.hpp"
#include "LoadData.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadModules(std::string filename)
{
	for (auto line : readFile(filename))
	{
		module_map.insert(loadModule(line));
	}
}

Module ResourceManager::getModule(std::string key)
{
	if (module_map.find(key) != module_map.end())
	{
		return module_map.at(key);
	}
	else
	{
		return Module();
		std::cout << "Tried to access non existant module, passing default-constructed module" << std::endl;
	}
}
