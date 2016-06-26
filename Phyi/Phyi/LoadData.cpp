#include "LoadData.hpp"
#include "ModuleTypes.hpp"

std::pair<std::string, Module> loadModule(std::vector<std::string> elements)
{
	return std::make_pair(elements[0],
			std::move(
			Module(
				static_cast<ModuleTypes::ModuleType>(std::stoi(elements[1])), // Convert integer to enum (No run time type check..)
				std::stoi(elements[2]),
				std::stoi(elements[3]),
				std::stoi(elements[4]),
				std::stoi(elements[5]),
				std::stoi(elements[6]),
				std::stoi(elements[7]),
				std::stoi(elements[8]))
			)
		);
}
