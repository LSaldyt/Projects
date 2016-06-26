#include "stdafx.h"

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Computer;
class NetworkAdapter;

class Connection //Intermediate object present in all network related objects
{
private:
	static int latest_IP;
	Computer* refers_to;
	NetworkAdapter* on;
	int IP;
	unordered_map<int, Connection*> connections;
	static unordered_map<int, Connection*> allConnections;

public:

	void set_refers_to(Computer*);

	void connect(Connection*);
	void disconnect(Connection*);
	void storeConnection(Connection*);
	void eraseConnection(Connection*);

	void setOn(NetworkAdapter* set_on) { on = set_on; }
	NetworkAdapter* getOn() { return on; }

	Computer* giveAccess();
	Connection* getConnect(int);

	vector<int> getConnections();
	static Connection* accessByIP(int query) { return allConnections[query]; }
	static int sizeOfConnections() { return allConnections.size(); }

	int getIP();
	void setIP(int);

	Connection();
	~Connection();
};

#endif