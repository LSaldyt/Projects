#include "ShipFrame.hpp"
#include "ModuleTypes.hpp"

ShipFrame::ShipFrame(int set_weapon_slots, int set_defense_slots, int set_system_slots, int set_integrity, int set_mass, int set_cargo_size, int set_cost)
{
	num_weapon_slots  = set_weapon_slots;
	num_defense_slots = set_defense_slots;
	num_system_slots  = set_system_slots;
	integrity         = set_integrity;
	max_integrity     = set_integrity;
	mass              = set_mass;
	num_cargoBaySize  = set_cargo_size;
	cost              = set_cost;
}

void ShipFrame::logFrame()
{
	for (auto& m : modules)
	{
		m->logModule();
	}
	engine->logModule();
	logDamage();
}

void ShipFrame::clean()
{
	auto isFunctional = [](auto&m){ return m->integrity > 0; };
	modules.erase(std::remove_if(modules.begin(), modules.end(), isFunctional),
		modules.end());
}

const int ShipFrame::getMass()
{
	return mass;
}

const int ShipFrame::engineForce()
{
	return engine->value;
}

const float ShipFrame::getAccel()
{
	return (float)engineForce() / (float)mass;
}

const bool ShipFrame::isAlive()
{
	return true;
}

const int ShipFrame::getCost()
{
	return cost;
}

//Definitions for adding modules

void ShipFrame::add(std::shared_ptr<Module> m)
{
	using namespace ModuleTypes;

	std::cout << m->getModuleType() << std::endl;

	switch (m->getModuleType())
	{
	case Weapon:
		if (openWeaponSlots() > 0)
		{
			modules.push_back(m);
			mass += m->mass;
			cost += m->getCost();
		}
		break;
	case Defense:
		if (openDefenseSlots() > 0)
		{
			modules.push_back(m);
			mass += m->mass;
			cost += m->getCost();
		}
		break;
	case Engine:
		engine = m;
		mass += m->mass;
		cost += m->getCost();
		break;
	default:
		std::cout << "Invalid Module Type" << std::endl;
		break;
	}
}

//Definitions for 

int ShipFrame::totalSlots()
{
	return num_weapon_slots + num_defense_slots + num_system_slots;
}

int ShipFrame::openSlots()
{
	return openWeaponSlots() + openDefenseSlots() + openSystemSlots();
}

int ShipFrame::openWeaponSlots()
{
	return num_weapon_slots - used_weapon_slots;
}

int ShipFrame::openDefenseSlots()
{
	return num_defense_slots - used_defense_slots;
}

int ShipFrame::openSystemSlots()
{
	return num_system_slots - used_system_slots;
}

void ShipFrame::damage(int amount)
{
	if (modules.size() > 0)
	{
		std::sort(
			modules.begin(), modules.end(),
			[](auto& m1, auto& m2)
		{return m1->getExternality() > m2->getExternality(); }
		);

		if (modules[0]->getExternality() > 0)
		{
			modules[0]->damage(amount);
		}
		else if (engine->getExternality() > 0 && engine->integrity > 0)
		{
			engine->damage(amount);
		}
		else
		{
			Damageable::damage(amount);
		}
	}
	else
	{
		Damageable::damage(amount);
	}
}

void ShipFrame::logDamage()
{
	int temp_actual = 0;
	int temp_max    = 0;
	for (auto& m : modules)
	{
		temp_actual += m->integrity;
		temp_max    += m->max_integrity;
		std::cout << ModuleTypes::toString(m->module_type) << ": \n";
		m->logDamage();
	}

	std::cout << "Frame: \n";
	Damageable::logDamage();

	std::cout << "Total: \n" <<
		temp_actual + integrity << "/" << temp_max + max_integrity << std::endl;
}
