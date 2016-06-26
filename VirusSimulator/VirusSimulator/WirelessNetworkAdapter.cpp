#include "stdafx.h"
#include "WirelessNetworkAdapter.hpp"

void NetworkAdapter::enable()
{
	enabled = true;
}

void NetworkAdapter::disable()
{
	enabled = false;
}

bool NetworkAdapter::checkStatus()
{
	return enabled;
}

NetworkAdapter::NetworkAdapter()
{
	model = "";
	setIsRouter(false);
}

NetworkAdapter::NetworkAdapter(string set_model, Computer* set_installedOn)
{
	model = set_model;
	installedOn = set_installedOn;
	adapterConnection.set_refers_to(set_installedOn);
	adapterConnection.setOn(this);
}

void NetworkAdapter::connect(Connection* new_connect)
{
	adapterConnection.connect(new_connect);
}

void NetworkAdapter::disconnect(Connection* end_connect)
{
	adapterConnection.disconnect(end_connect);
}

void NetworkAdapter::set_installedOn(Computer* set_installedOn)
{
	installedOn = set_installedOn;
	adapterConnection.set_refers_to(set_installedOn);
}