#include "stdafx.h"

#ifndef WIRELESSNETWORKADAPTER_HPP
#define WIRELESSNETWORKADAPTER_HPP

#include "Hardware.hpp"

#include "Connection.hpp"

class NetworkAdapter : public Hardware
{
protected:
	bool enabled;
	Connection adapterConnection;
	bool isRouter;

public:
	void enable();
	void disable();

	bool checkStatus();
	bool getIsRouter() { return isRouter; };
	void setIsRouter(bool set) { isRouter = set; } //Technically this could be static, as could the above, but whatever.

	void connect(Connection*);
	void disconnect(Connection*);

	void set_installedOn(Computer * set_installedOn);

	Connection* getConnection() { return &adapterConnection; }

	NetworkAdapter();
	NetworkAdapter(string, Computer*);
	~NetworkAdapter() {};
};



#endif