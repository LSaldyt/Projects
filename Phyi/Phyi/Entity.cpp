#include "Entity.hpp"
#include "Includes.hpp"

//Make sure this constructor always gets called, as seen below
Entity::Entity(float set_mass, sf::Vector2f set_pos, sf::Vector2f set_velocity) 
	: forces(std::make_shared<std::vector<Force>>(std::vector<Force>())), awaiting_action(false), mass(set_mass), velocity(set_velocity), owner("")
{
	setPosition(set_pos);
}

Entity::Entity(sf::Texture& text, float set_mass, sf::Vector2f set_pos, sf::Vector2f set_velocity)
	: Entity(set_mass, set_pos, set_velocity) //Call the default constructor
{
	this->setTexture(text);
}

Entity::~Entity(){}

const float Entity::getMass()   { return mass; }
const int   Entity::getSortBy() { return (int)getPosition().x + (int)getPosition().y * sortOffset; }

void Entity::setVelocity(sf::Vector2f set_velocity)
{
	this->velocity = set_velocity;
}

const sf::Vector2f Entity::getVelocity()
{
	return this->velocity;
}

void Entity::setApproach(sf::Vector2f)
{
}

const bool Entity::isAlive()
{
	return true;
}

sf::Vector2f Entity::getCenter()
{
	return sf::Vector2f(getPosition().x + getGlobalBounds().width / 2,
		getPosition().y + getGlobalBounds().height / 2);
}

void Entity::action(Chunk<Entity> * board)
{
	std::cout << "Action" << std::endl;
	awaiting_action = false;
}

const bool Entity::isAwaitingAction()
{
	return awaiting_action;
}

const std::string& Entity::getOwner()
{
	return owner;
}

void Entity::setOwner(std::string set_owner)
{
	owner = set_owner;
}

void Entity::doDraw(sf::RenderTarget & target)
{
	target.draw(*this);
}

void Entity::clean()
{
}

void Entity::update()
{
	auto currentPos = getPosition();

	for (Force& f : *forces)
	{
		velocity += sf::Vector2f(
			f.getMagnitude() * cosf(f.getAngle()) / mass,
			f.getMagnitude() * sinf(f.getAngle()) / mass
			);
	}

	forces->clear();

	move(velocity);
}

void Entity::apply(Force f)
{
	forces->push_back(f);
}

void Entity::collide(Entity* e)
//So that Entity can have a derived class in the future (this isn't an allocated pointer, just a more powerful reference)
{
	float total_mass = mass + e->getMass();

	auto calc_velocity = [total_mass](float m1, float m2, float v1, float v2) 
	{
		return ((m1 - m2) * v1) / total_mass + ((2.0f * m2 * v2) / total_mass);
	};

	auto e_vx_final = calc_velocity(e->getMass(), mass, e->getVelocity().y, velocity.y);
	auto e_vy_final = calc_velocity(e->getMass(), mass, e->getVelocity().y, velocity.y);

	auto   vx_final = calc_velocity(mass, e->getMass(), velocity.x, e->getVelocity().x);
	auto   vy_final = calc_velocity(mass, e->getMass(), velocity.y, e->getVelocity().y);

	e->velocity.x = e_vx_final;
	e->velocity.y = e_vy_final;

	velocity.x = vx_final;
	velocity.y = vy_final;
}

bool Entity::checkWith(Entity& e)
{
	return e.getGlobalBounds().intersects(this->getGlobalBounds());
}
//Operators for comparing Entity Types

bool operator< (Entity &e1, Entity &e2)
{
	return e1.getSortBy() < e2.getSortBy();
}

bool operator> (Entity &e1, Entity &e2)
{
	return e1.getSortBy() > e2.getSortBy();
}

bool operator<= (Entity &e1, Entity &e2)
{
	return e1.getSortBy() <= e2.getSortBy();
}

bool operator>= (Entity &e1, Entity &e2)
{
	return e1.getSortBy() >= e2.getSortBy();
}

bool operator== (Entity &e1, Entity &e2)
{
	return e1.getSortBy() == e2.getSortBy();
}