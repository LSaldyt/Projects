#pragma once
#include "Includes.hpp"

struct Damageable
{
	int max_integrity;
	int integrity;

	virtual void Damageable::damage(int amount)
	{
		integrity -= amount;
		if (integrity < 0) integrity = 0;
	}

	virtual double Damageable::percentIntegrity()
	{
		return (double)integrity / (double)max_integrity;
	}

	Damageable::Damageable(int set_integrity=0)
	{
		integrity     = set_integrity;
		max_integrity = set_integrity;
	}

	virtual void Damageable::logDamage()
	{
		std::cout << "Integrity" << integrity <<
			"/" << max_integrity << "\n"
			<< std::endl;
	}
};