#include "stdafx.h"
#include "Connection.hpp"

//All IP addresses are assigned ID's starting at 1
int Connection::latest_IP = 1;
unordered_map<int, Connection*> Connection::allConnections;

void Connection::set_refers_to(Computer* set_refers_to)
{
	refers_to = set_refers_to;
}

void Connection::connect(Connection* new_connection) //Istantiates a connection with another connection object, then stores its own information in the connection object it just connected to :))
{
	if (connections.find(new_connection->getIP()) == connections.end())
	{
		connections.insert(std::pair<int, Connection*>(new_connection->getIP(), new_connection));
		cout << "000.000.000.0"; //Mimicry!
		cout << IP;
		cout << " Successfully connected with IP: ";
		cout << "000.000.000.0";
		cout << new_connection->getIP() << endl;
	}
		new_connection->storeConnection(this);
}

void Connection::storeConnection(Connection* store_connection)
{
	if (connections.find(store_connection->getIP()) == connections.end())
	{
		connections.insert(std::pair<int, Connection*>(store_connection->getIP(), store_connection));
		cout << "000.000.000.0"; //Mimicry!
		cout << IP;
		cout << " Successfully stored connection to IP: ";
		cout << "000.000.000.0";
		cout << store_connection->getIP() << endl;
	}
}

void Connection::disconnect(Connection* end_connection)
{
	connections.erase(end_connection->getIP());
	cout << "000.000.000.0"; //Mimicry!
	cout << IP;
	cout << "Successfully disconnected to connection with Serial IP: ";
	cout << "000.000.000.0"; 
	cout << end_connection->getIP() << endl;
	end_connection->eraseConnection(this);
}

void Connection::eraseConnection(Connection* erase_connection)
{
	connections.erase(erase_connection->getIP());
	cout << "Successfully erased connection to IP: ";
	cout << "000.000.000.0";
	cout << erase_connection->getIP() << endl;
}

int Connection::getIP()
{
	return IP;
}

void Connection::setIP(int set_ip)
{
	if (set_ip > latest_IP)
	{
		IP = set_ip;
	}
}

Connection::Connection()
{
	latest_IP++;
	IP = latest_IP;

	allConnections.insert(std::pair<int, Connection*>(IP, this));
}

Connection::~Connection()
{
	if (IP = latest_IP)
	{
		latest_IP--; //Prevent skipping of IPs when creating duplicate objects, if possible.
	}
	allConnections.erase(IP);
}

Computer* Connection::giveAccess()
{
	return refers_to;
}

Connection* Connection::getConnect(int access_IP)
{
	return connections[access_IP];
}

vector<int> Connection::getConnections()
{
	vector<int> keys;
	keys.reserve(connections.size());
	//Pretty similar to USB_Drive.autorun()
	//Extracts keys from list of connections then accesses all elements that each key refers to

	for (auto kv : connections) {
		keys.push_back(kv.first);
	}
	return keys;
}