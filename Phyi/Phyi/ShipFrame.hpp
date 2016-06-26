#pragma once
#include "Includes.hpp"
#include "Damageable.hpp"
#include "Module.hpp"

struct ShipFrame : Damageable
{
	ShipFrame(int set_weapon_slots=0, int set_defense_slots=0, int set_system_slots=0, 
			  int set_integrity=0, int set_mass=0, int set_cargo_size=0, int set_cost=0);
	void add(std::shared_ptr<Module>);

	int totalSlots();
	int openSlots();
	int openWeaponSlots();
	int openDefenseSlots();
	int openSystemSlots();

	virtual void damage(int);
	virtual void logDamage();

	void logFrame();
	void clean();
	const int getMass();
	const int engineForce();
	const float getAccel();
	const bool isAlive();
	const int getCost();

	int used_weapon_slots  = 0;
	int used_defense_slots = 0;
	int used_system_slots  = 0;

	int num_weapon_slots;
	int num_defense_slots;
	int num_system_slots;

	int num_cargoBaySize;

private:
	std::vector<std::shared_ptr<Module>> modules;
	std::shared_ptr<Module> engine;

	int mass;
	int cost;
};