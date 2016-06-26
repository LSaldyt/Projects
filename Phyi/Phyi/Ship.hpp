#pragma once
#include "Entity.hpp"
#include "ShipFrame.hpp"
#include "Projectile.hpp"

class Ship :
	public Entity
{
public:
	Ship();
	~Ship();

	void logShip();
	void setFrame(ShipFrame);

	const virtual float getMass();

	virtual void update();
	virtual void damage(int);
	virtual void logDamage();
	virtual void collide(Entity* e);
	virtual void action(Chunk<Entity>* chunk);

	void shoot(float angle, Chunk<Entity>* chunk);

	void accelerate();
	void decelerate();
	void stop();
	void approach();
	void correctSpeed();
	std::pair<bool, bool> movingToward(sf::Vector2f);
	void turnTo(Angle angle);
	void setApproach(sf::Vector2f);

	const bool isAlive();

private:
	bool shooting;
	bool approaching;
	bool attacking;
	bool targeting_enemy;

	sf::Vector2f target;
	float target_angle;

	ShipFrame frame;
};

