#pragma once
#include "Commander.hpp"
class Player :
	public Commander
{
public:
	Player();
	~Player();

	int funds = 10000000;
};

