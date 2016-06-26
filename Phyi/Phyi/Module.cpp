#include "Module.hpp"

void Module::logModule()
{
	using namespace ModuleTypes;

	auto type = toString(module_type, sub_type);

	std::cout << toString(module_type) + "Module" << "\n\t"
		<< "Type: " << type << "\n\t"
		<< "State: " << toString(state) << "\n\t"
		<< "Power Usage: " << power_usage << "\n\t" <<
		"Mass: " << mass <<
		std::endl;
}

const int Module::getExternality()
{
	return externality;
}

Module::Module(int set_power_usage, int set_mass) : power_usage(set_power_usage), mass(set_mass)
{
	state = ModuleTypes::Normal;
}


Module::Module(ModuleTypes::ModuleType set_module_type, int set_sub_type, 
	int set_externality, int set_value, int set_power_usage, int set_mass, int set_life, int set_cost) 
	  : Module(set_power_usage, set_mass)
{
	externality = set_externality;
	module_type = set_module_type;
	value = set_value;
	sub_type = set_sub_type;
	integrity = set_life;
	max_integrity = set_life;
	cost = set_cost;
}

Module::~Module()
{
}


const ModuleTypes::ModuleType Module::getModuleType()
{
	return module_type;
}

const int Module::getCost()
{
	return cost;
}
