#include "stdafx.h"
#include "Router.hpp"

Router::Router()
{
	adapterConnection.setOn(this);
	setIsRouter(true);
}

Router::~Router()
{

}