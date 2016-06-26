#pragma once
#include "Damageable.hpp"
#include "ModuleTypes.hpp"

class Module : public Damageable
{
public:
	Module(int set_power_usage = 0, int set_mass = 0);
	Module(ModuleTypes::ModuleType set_module_type, int set_sub_type, int set_externality, int set_value=0,
		int set_power_usage=0, int set_mass=0, int set_life=0, int set_cost=0); 
	~Module();

	ModuleTypes::State state;
	ModuleTypes::ModuleType module_type;
	int sub_type;
	int value;

	int power_usage;
	int mass;

	const ModuleTypes::ModuleType getModuleType();
	const int getCost();
	void logModule();

	const int getExternality();
private:
	int externality;
	int cost;
};
