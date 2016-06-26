#pragma once
#include "Includes.hpp"
#include "Angle.hpp"

class Entity;

template <class T>
int numDigits(T number)
{
	int digits = 0;
	while (number) 
	{
		number /= 10;
		digits++;
	}
	return digits;
}

sf::Vector2f operator+  (sf::Vector2f& v1, sf::Vector2f& v2);
sf::Vector2f operator-  (sf::Vector2f& v1, sf::Vector2f& v2);
void         operator+= (sf::Vector2f& v1, sf::Vector2f& v2);
void         operator-= (sf::Vector2f& v1, sf::Vector2f& v2);

enum Direction
{
	Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight, None
};

float getAngleBetween(sf::Vector2f pos1, sf::Vector2f pos2);

float getDistanceBetween(sf::Vector2f, sf::Vector2f);

float getStoppingDistance(float velocity, float accel);

float toMagnitude(sf::Vector2f velocity);

void moveAt(Angle angle, Entity& entity, float amount);