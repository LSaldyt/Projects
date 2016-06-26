#pragma once
#include "Force.hpp"
#include "Damageable.hpp"
#include "Chunk.hpp"

class Entity :
	public sf::Sprite, public Damageable
{
public:
	static const int sortOffset = 10000;

	Entity(float set_mass = 1, sf::Vector2f = sf::Vector2f(0.0f, 0.0f), sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));
	Entity(sf::Texture& text, float set_mass, sf::Vector2f set_pos, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));
	~Entity();

	virtual void  update   ();
	virtual void  apply    (Force f);
	virtual void  collide  (Entity* e);
	virtual void  doDraw   (sf::RenderTarget& target);
	virtual void  clean    ();
	 
	virtual bool  checkWith(Entity& e);

	virtual const int getSortBy();

	const virtual float        getMass();

	void setVelocity(sf::Vector2f);
	const sf::Vector2f getVelocity();

	virtual void setApproach(sf::Vector2f);

	virtual const bool isAlive();

	sf::Vector2f getCenter();

	virtual void action(Chunk<Entity>* board);
	const bool isAwaitingAction();
	
	const std::string& getOwner();
	void setOwner(std::string);

protected:

	std::shared_ptr<std::vector<Force>> forces;

	float mass;

	sf::Vector2f velocity;

	bool awaiting_action;
	std::string owner;
};

bool operator<  (Entity& e1, Entity& e2);
bool operator>  (Entity& e1, Entity& e2);
bool operator<= (Entity& e1, Entity& e2);
bool operator>= (Entity& e1, Entity& e2);
bool operator== (Entity& e1, Entity& e2);
