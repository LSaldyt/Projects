#pragma once
#include "Includes.hpp"

namespace ModuleTypes
{
	enum State
	{
		Damaged, Normal
	}; 

	enum ModuleType
	{
		Engine, Weapon, Defense, System
	};

	enum EngineTypes
	{
		Electric, Fueled
	};

	enum WeaponTypes
	{
		Puncture, Heat
	};

	enum DefenseTypes
	{
		Shield, Armor
	};

	std::string toString(ModuleType type);
	std::string toString(State state);
	std::string toString(ModuleType type, int);
	std::string toString(EngineTypes type);
	std::string toString(WeaponTypes type);
	std::string toString(DefenseTypes type);
};
