#pragma once

#ifndef TO_RADIANS
#define TO_RADIANS 0.0174533f
#endif

#ifndef TO_DEGREES
#define TO_DEGREES 57.2958f
#endif

struct Angle
{
private:
	float angle;

public:

	Angle::Angle(float set_value)
	{
		set(set_value);
	}

	Angle::Angle()
	{
		angle = 0;
	}

	void Angle::set(float set_value)
	{
		while (set_value > 360) //Can't call modulus on a floating point number!
		{
			set_value -= 360;
		}
		if (set_value < 0)
		{
			set_value = 360 - abs(set_value);
		}
		angle = set_value;
	}

	const float value()
	{
		return angle;
	}
};