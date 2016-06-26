#include "stdafx.h"
#include "Software.hpp"
#include "Virus.hpp"
#include "Computer.hpp"
#include "USB_Drive.hpp"
#include "USBHub.hpp"
#include "Connection.hpp"
#include "Router.hpp"

Virus* Virus::copy()
{
	Virus* copy = new Virus();
	*copy = *this;
	return copy;
}

Virus::Virus()
{

}

Virus::Virus(string set_name, string set_version)
{
	setName(set_name);
	setVersion(set_version);
}

Virus::~Virus()
{

}

void Virus::spreadUSB()
{
	if (installedOn != NULL)
	{
		//A basic function to find susceptable USB ports or hard drives (But nothing else)
		//installedOn->checkHub(); //Instead of printing, we could make this return booleans (printing the status was only for testing)
		//previous line commented out for now to keep output more concise
		installedOn->enableHub(); //Enables the hub to install itself to any available drives

		int vulnerableSlots = installedOn->accessHub()->getFullSlots();

		for (int i = 0; i < vulnerableSlots; i++)
		{
			USB_Drive * currentDrive = installedOn->accessHub()->accessSlots()->at(i).accessDrive();
			if (currentDrive != NULL)
			{
				currentDrive->Install(this, "default", installedOn);
				//Pretty verbose, but this Installs the virus to all other Drives on the system
				cout << "Infected USB Drive in slot " << i << endl;
			}	
		}

		installedOn->Install(this, "default"); //Installs itself to the computer harddrive
		cout << "Infected Harddrive" << endl;
	}
	else
	{
		cout << "No Path" << endl;
	}
}

void Virus::spreadNetwork()
{
	cout << "Initializing " << name << endl;
	if (installedOn != NULL)
	{
		
		vector<int> vulnerableConnectionIPs;
		{ //Virtual Block
			vector<int> preliminaryIPs = installedOn->getNetworkAdapter()->getConnection()->getConnections();
			//Build a list of vulnerable connections
			for (int i = 0; i < preliminaryIPs.size(); i++)
			{
				Connection* currentConnect = installedOn->getNetworkAdapter()->getConnection()->getConnect(preliminaryIPs[i]);
				if (currentConnect->getOn()->getIsRouter())
				{
					cout << "Router Found at " << currentConnect->getIP() << endl;
					vector<int> routerConnectionIPs = currentConnect->getConnections();

					for (int k = 0; k < routerConnectionIPs.size(); k++)
					{
						if (!(std::find(vulnerableConnectionIPs.begin(), vulnerableConnectionIPs.end(), routerConnectionIPs[k]) != vulnerableConnectionIPs.end())
							&& vulnerableConnectionIPs.size() < ipGatherLimit
							&& !Connection::accessByIP(routerConnectionIPs[k])->getOn()->getIsRouter())
						{
							vulnerableConnectionIPs.push_back(routerConnectionIPs[k]);
							cout << "Router returned new IP: " << routerConnectionIPs[k] << endl;
						}
					}

				}
				else
				{
					vulnerableConnectionIPs.push_back(preliminaryIPs[i]);
				}
			}
		}
		for (int i = 0; i < vulnerableConnectionIPs.size(); i++)
		{
			installedOn->getNetworkAdapter()->getConnection()->connect(Connection::accessByIP(vulnerableConnectionIPs[i]));
		}

		//For each vulnerable connection...

		{ //Virtual block 
			vector <int> successfulConnects = installedOn->getNetworkAdapter()->getConnection()->getConnections();
			for (int i = 0; i < successfulConnects.size(); i++)
			{
				cout << "Current size of connections: " << installedOn->getNetworkAdapter()->getConnection()->getConnections().size() << endl;
				Connection* currentConnect = installedOn->getNetworkAdapter()->getConnection()->getConnect(successfulConnects[i]);
				if (currentConnect != NULL)
				{
					if (!currentConnect->getOn()->getIsRouter())
					{
						Computer* accessRequest = currentConnect->giveAccess();
						if (accessRequest != NULL)
						{
							accessRequest->Install(this, "default");
						}
						else
						{
							cout << "Access Request not found" << endl;
						}
					}
					else
					{
						cout << successfulConnects[i] << " Is a router " << endl;
					}
				}
				else
				{
					cout << "Current Connection not found" << endl;
				}
			}
		}
		installedOn->Install(this, "default"); //Installs itself to the computer harddrive
		cout << "Infected Harddrive" << endl;
	}
	else
	{
		cout << "No Path" << endl;
	}
}

Software* Virus::open() //override software's open()
{
	//Create a new instance of a piece of "software"
	isOpen = true;
	instances.push_back(Instance());

	spreadUSB(); // :)
	spreadNetwork();
	cout << "Virus Opened :P" << endl; //To be cute
	return this;
}

Virus& Virus::operator=(const Virus& cSource)
{
	Software::operator=(cSource);

	return *this;
}