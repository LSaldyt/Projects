#pragma once
#include "Includes.hpp"
#include "Angle.hpp"

class Force
{
public:
	Force();
	Force::Force(Angle set_angle, float set_magnitude);
	~Force();

	const float getAngle();
	const float getMagnitude();

private:
	Angle angle;
	float magnitude_value;
};

