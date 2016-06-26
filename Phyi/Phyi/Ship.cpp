#include "Ship.hpp"
#include "Includes.hpp"
#include "Board.hpp"

Ship::Ship() : approaching(false), shooting(true), attacking(true), targeting_enemy(false)
{
	awaiting_action = true;
}

Ship::~Ship()
{
}

void Ship::logShip()
{
	std::cout << "Ship:\n" << "\n\t"
		"Total Slots: " << frame.totalSlots()  << "\n\t"
		"Open Slots: "  << frame.openSlots()   << "\n"
		<< std::endl;
	frame.logFrame();
}

void Ship::setFrame(ShipFrame set_frame)
{
	frame = set_frame;
	mass = (float)frame.getMass();
}

const float Ship::getMass()
{
	return (float)frame.getMass();
}

void Ship::update()
{
	awaiting_action = true;
	Entity::update();
	if (approaching)
	{
		approach();
	}

	frame.clean();
}

void Ship::damage(int amount)
{
	frame.damage(amount);
}

void Ship::logDamage()
{
	frame.logDamage();
}

void Ship::collide(Entity * e)
{
	/*
	Entity::collide(e);
	
	auto angle_between    = getAngleBetween   (getCenter(), e->getCenter());
	auto distance_between = getDistanceBetween(getCenter(), e->getCenter());
	if (distance_between < getGlobalBounds().width )
	{
		moveAt(Angle(angle_between), *e, distance_between / 2.0f);
		moveAt(Angle(angle_between + 180.0f), *this, distance_between / 2.0f);
	}
	*/
}

void Ship::action(Chunk<Entity> * chunk)
{
	for (auto& e : chunk->entities)
	{
		if (e->getOwner() != this->getOwner())
		{
			if (shooting)
			{
				shoot(getAngleBetween(getPosition(), e->getPosition()), chunk);
				shooting = true;
			}
			break;
		}
	}
	awaiting_action = false;
}

void Ship::shoot(float angle = 0, Chunk<Entity>* chunk=NULL)
{
	Projectile test_projectile(20, 10000);
	sf::Vector2f pos(getPosition().x + cosf(TO_RADIANS * angle) * getGlobalBounds().width * 1.5f,
					 getPosition().y + sinf(TO_RADIANS * angle) * getGlobalBounds().height * 1.5f);
	test_projectile.setOrigin(test_projectile.getCenter());
	test_projectile.setPosition(pos);
	test_projectile.apply(Force(Angle(angle), 1.0f));
	test_projectile.setTexture(Board<Entity>::texture_map.get("projectile"));
	chunk->add(std::make_shared<Projectile>(test_projectile));
	shooting = false;
}

void Ship::accelerate()
{
	apply(Force(Angle(getRotation()), (float)frame.engineForce()));
}

void Ship::decelerate()
{
	if (abs(toMagnitude(velocity)) > frame.getAccel())
	{
		apply(Force(Angle(getRotation() + 180), (float)frame.engineForce()));
	}
	else
	{
		stop();
	}
}

void Ship::stop()
{
	velocity = sf::Vector2f(0.0f, 0.0f);
}

void Ship::approach()
{
	target_angle = getAngleBetween(getPosition(), target);
	turnTo(Angle(target_angle));

	if (getDistanceBetween(getPosition(), target) < getGlobalBounds().width * 2.0f)
	{
		stop();
		setRotation(target_angle);
	}
	else
	{
		correctSpeed();
	}
}

void Ship::correctSpeed()
{

	float stopping_distance = sqrt(pow(getStoppingDistance(velocity.x, frame.getAccel()), 2.0f) + pow(getStoppingDistance(velocity.x, frame.getAccel()), 2.0f));
	auto moving_toward = movingToward(target);


	if (stopping_distance < getDistanceBetween(getPosition(), target) - getGlobalBounds().width / 2.0f &&
		moving_toward.first && moving_toward.second)
	{
		accelerate();
	}
	else if (!moving_toward.first)
	{
		if (target.x > getPosition().x)
		{
			velocity.x += frame.getAccel() / 2.0f;
		}
		else
		{
			velocity.x -= frame.getAccel() / 2.0f;
		}
	}
	else if (!moving_toward.second)
	{
		if (target.y > getPosition().y)
		{
			velocity.y += frame.getAccel() / 2.0f;
		}
		else
		{
			velocity.y -= frame.getAccel() / 2.0f;
		}
	}
	else
	{
		decelerate();
	}
}

std::pair<bool, bool> Ship::movingToward(sf::Vector2f pos)
{
	auto towardX = false;
	auto towardY = false;

	auto epsilon = 1.0f;

	if ((getPosition().x < pos.x - epsilon && velocity.x > 0.0f) ||
		(getPosition().x > pos.x - epsilon && velocity.x < 0.0f))
	{
		towardX = true;
	}
	if((getPosition().y < pos.y - epsilon && velocity.y > 0.0f) ||
		getPosition().y > pos.y - epsilon && velocity.y < 0.0f)
	{
		towardY = true;
	}

	return std::make_pair(towardX, towardY);
}

void Ship::turnTo(Angle angle)
{
	if (abs(getRotation() - angle.value()) > 1.0)
	{	
		float max_rotate = 30.0f * frame.getAccel();
		if (abs(getRotation() - angle.value()) < max_rotate)
		{
			setRotation(angle.value());
		}
		else if (Angle(getRotation() - angle.value()).value() < Angle(angle.value() - getRotation()).value())
		{
			rotate(-max_rotate);
		}
		else
		{
			rotate(max_rotate);
		}
	}
}

void Ship::setApproach(sf::Vector2f pos)
{
	stop();
	approaching = true;
	target_angle = getAngleBetween(getPosition(), pos);
	target = pos;
}

const bool Ship::isAlive()
{
	return frame.isAlive();
}
