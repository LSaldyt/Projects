#include "Force.hpp"

Force::Force()
{
	angle = 0;
	magnitude_value = 0;
}

Force::Force(Angle set_angle, float set_magnitude)
{
	angle = set_angle;
	magnitude_value = set_magnitude;
}

Force::~Force(){}

const float Force::getAngle()
{
	return TO_RADIANS * angle.value();
}

const float Force::getMagnitude()
{
	return magnitude_value;
}