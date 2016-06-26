#include "Physics.hpp"
#include "Angle.hpp"
#include "Entity.hpp"

sf::Vector2f operator+  (sf::Vector2f& v1, sf::Vector2f& v2)
{
	return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
}

sf::Vector2f operator-  (sf::Vector2f& v1, sf::Vector2f& v2)
{
	return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
}

void operator+= (sf::Vector2f& v1, sf::Vector2f& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
}

void operator-= (sf::Vector2f& v1, sf::Vector2f& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
}

float getAngleBetween(sf::Vector2f pos1, sf::Vector2f pos2)
{
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;

	return atan2f(dy, dx) * TO_DEGREES;
}

float getDistanceBetween(sf::Vector2f pos1, sf::Vector2f pos2)
{
	float dx = abs(pos1.x - pos2.x);
	float dy = abs(pos1.x - pos2.x);
	return sqrt(dx * dx + dy * dy);
}

float getStoppingDistance(float velocity, float accel)
{
	float stopping_time = abs(velocity / accel);
	return abs(velocity) * stopping_time - 0.5f * abs(accel) * stopping_time * stopping_time;
}

float toMagnitude(sf::Vector2f velocity)
{
	return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

void moveAt(Angle angle, Entity & entity, float amount)
{
	entity.move(amount * cosf(angle.value() * TO_RADIANS), amount * sinf(angle.value() * TO_RADIANS));
}
