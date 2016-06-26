#include "ModuleTypes.hpp"

std::string ModuleTypes::toString(ModuleType type)
{
	std::string s;
	switch (type)
	{
	case ModuleTypes::Engine:
		s = "Engine";
		break;
	case ModuleTypes::Weapon:
		s = "Weapon";
		break;
	case ModuleTypes::Defense:
		s = "Defense";
		break;
	case ModuleTypes::System:
		s = "System";
		break;
	default:
		s = "";
		break;
	}
	return s;
}


std::string ModuleTypes::toString(State state)
{
	std::string s;
	switch (state)
	{
	case ModuleTypes::Damaged:
		s = "Damaged";
		break;
	case ModuleTypes::Normal:
		s = "Normal";
		break;
	default:
		s = "";
		break;
	}
	return s;
}

std::string ModuleTypes::toString(ModuleType type, int sub_type)
{
	std::string s;
	switch (type)
	{
	case Engine:
		s = toString((EngineTypes)sub_type);
		break;
	case Weapon:
		s = toString((WeaponTypes)sub_type);
		break;
	case Defense:
		s = toString((DefenseTypes)sub_type);
		break;
	case System:
		s = "";
		break;
	default:
		s = "";
		break;
	}
	return s;
}

std::string ModuleTypes::toString(EngineTypes type)
{
	std::string s;
	switch (type)
	{
	case ModuleTypes::Electric:
		s = "Electric";
		break;
	case ModuleTypes::Fueled:
		s = "Fueled";
		break;
	default:
		break;
	}
	return s;
}

std::string ModuleTypes::toString(WeaponTypes type)
{
	std::string s;
	switch (type)
	{
	case ModuleTypes::Puncture:
		s = "Puncture";
		break;
	case ModuleTypes::Heat:
		s = "Heat";
		break;
	default:
		s = "";
		break;
	}
	return s;
}

std::string ModuleTypes::toString(DefenseTypes type)
{
	std::string s;
	switch (type)
	{
	case ModuleTypes::Shield:
		s = "Shield";
		break;
	case ModuleTypes::Armor:
		s = "Armor";
		break;
	default:
		s = "";
		break;
	}
	return s;
}