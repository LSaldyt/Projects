#include "Projectile.hpp"


Projectile::~Projectile()
{
}

Projectile::Projectile(int set_damage_amount, int set_life, float set_mass, sf::Vector2f set_pos, sf::Vector2f velocity) 
	: life(set_life), damage_amount(set_damage_amount)
{
	Entity::Entity(set_mass, set_pos, velocity);

}

Projectile::Projectile(int set_life, sf::Texture & text, float set_mass, sf::Vector2f set_pos, sf::Vector2f velocity)
{
	Entity::Entity(text, set_mass, set_pos, velocity);
	life = set_life;
}

void Projectile::update()
{
	Entity::update();
	life -= 1;
}

void Projectile::collide(Entity* e)
{
	life = 0;
	e->damage(damage_amount);
	e->logDamage();
}

const bool Projectile::isAlive()
{
	return life > 0;
}
