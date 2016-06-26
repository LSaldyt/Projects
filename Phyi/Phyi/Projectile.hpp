#pragma once
#include "Entity.hpp"
class Projectile :
	public Entity
{
public:
	~Projectile();

	Projectile(int damage_amount = 1, int set_life = 0, float set_mass = 1, sf::Vector2f = sf::Vector2f(0.0f, 0.0f), sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));
	Projectile(int life, sf::Texture& text, float set_mass, sf::Vector2f set_pos, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));

	virtual void  update();

	virtual void  collide(Entity* e);
	virtual const bool isAlive();

private:
	int life;
	int damage_amount;
};

