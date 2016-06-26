#include "stdafx.h"

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "WirelessNetworkAdapter.hpp"
#include "Firewall.hpp"

class Router : public NetworkAdapter
{
private:
	bool isRouter;
	Firewall routerFirewall; //In the future this will manage connections etc..

	//Its surprising how empty this class is, considering its usefulness

public:

	Router();
	~Router();

};

#endif
