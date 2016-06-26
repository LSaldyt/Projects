#include "stdafx.h"
#include "Computer.hpp"
#include "Harddrive.hpp"
#include "WirelessNetworkAdapter.hpp"
#include "OperatingSystem.hpp"
#include "Folder.hpp"
#include "Browser.hpp"

Computer::Computer()
{
	computerNetworkAdapter = NetworkAdapter("Intel Dual Band Wireless AC 7260", this);
	toggleAdapter();
	computerUSBhub = USB_hub(4, this);
	enableHub();
	computerDrive = Harddrive(true);
	setDrive("Seagate", true, 1024, "C");
	computerDrive.addFolder("default");
	computerProcessor.CreateProcessor("i5", 2, 2.0);
	computerEthernetPort = EthernetPort();
	browser = Browser("chrome", "1.21.1");

	//computerDrive.addFolder("default");
	/*
	setDrive("Seagate", true, 1024, "C");
	ConstructProcessor(2.0, 2); //2.0 Ghz and Dou-core, as some sort of standard
								//Nothing needed here yet...
	computerCPU.Init();
	*/
}

Computer::Computer(OperatingSystem OS)
{
	computerNetworkAdapter = NetworkAdapter("Intel Dual Band Wireless AC 7260", this);
	toggleAdapter();
	computerUSBhub = USB_hub(4, this);
	enableHub();
	computerDrive = Harddrive(true);
	setDrive("Seagate", true, 1024, "C");
	computerDrive.addFolder("default");
	computerProcessor.CreateProcessor("i5", 2, 2.0);
	computerEthernetPort = EthernetPort();
	browser = Browser("chrome", "1.21.1");

	InstallOS(OS);

	//computerDrive.addFolder("default");
	/*
	setDrive("Seagate", true, 1024, "C");
	ConstructProcessor(2.0, 2); //2.0 Ghz and Dou-core, as some sort of standard
	//Nothing needed here yet...
	computerCPU.Init();
	*/
}


void Computer::ConstructProcessor(float cpuSpeed, int cpuCores)
{
	timeSteps = 0; //gotta init it somewhere.
	setProcessor(GenerateCorporateNameUsingUser(), cpuCores, cpuSpeed); //This is setting the model of the processor as a randomly generated name
	//If you meant to do this then alright though
}

string Computer::GenerateCorporateNameUsingUser() 
{
	User corporateTemporaryUser;
	return corporateTemporaryUser.generateRandomName();
}


Computer::~Computer() {}

void Computer::start()
{
	if (!on)
	{
		on = true;
	}
}

void Computer::login(string username, string password)
{
	
	//TODO: Make this variable based on what is done on login.
	timeSteps += 15 / getProcessorSpeed(16); //Neato :)

	computerOS.login(username, password);
}

void Computer::logout(string username)
{

	//TODO: Make this variable based on what is done on logout.
	timeSteps += 15 / getProcessorSpeed(16);
	computerOS.logout(username);
}

void Computer::restart()
{
	if (on)
	{
		on = false;
	}
	//1 core boot on system. Later we can add OS related variables for this kind of stuff
	timeSteps += 30 / getProcessorSpeed(1);

	//...
	//This should have some sort of implementation to close all processes, but for now this is fine

	on = true;
}

void Computer::shutdown()
{
	if (on)
	{
		timeSteps += 30 / getProcessorSpeed(1);
		on = false;
	}
}

void Computer::checkOn()
{
	if (on)
	{
		cout << "On" << endl;
	}
	else
	{
		cout << "Off" << endl;
	}
}

void Computer::InstallOS(OperatingSystem installation)
{
	timeSteps += 1200 / getProcessorSpeed(4);
	computerOS = installation;
}

void Computer::Install(Software* installation, string folder) 
{
	computerDrive.Install(installation, folder, this);
	cout << "Successfully Installed " << installation->getName() << endl;
}

void Computer::Install(Browser installation)
{
	browser = installation;
	browser.setInstalledOn(this);
}

Software* Computer::open(string folder, string filename)
{
	if (on)
	{
		timeSteps += 0.3 / getProcessorSpeed(4);
		return computerDrive.open(folder, filename);
	}
	else
	{
		cout << "Computer Unpowered" << endl;
	}
}

void Computer::close(string folder, string filename)
{
	if (on)
	{
		timeSteps += 0.1 / getProcessorSpeed(4);
		computerDrive.close(folder, filename);
	}
	else
	{
		cout << "Computer Unpowered" << endl;
	}
}

void Computer::checkSoftware(string folder, string filename)
{
	if (on)
	{
		computerDrive.access(folder)->printInstances(filename);
	}
	else
	{
		cout << "Computer Unpowered" << endl;
	}
}

void Computer::setProcessor(string model, int cores, float speed)
{
	
	computerCPU.CreateProcessor(model, cores, speed);

}

float Computer::getProcessorSpeed(int CPUThreads) {
	return computerProcessor.ReturnProcessorSpeed(CPUThreads);
}

void Computer::getProcessor(){
	computerProcessor.ReturnProcessor();
}

void Computer::setAdapter(string model)
{
	computerNetworkAdapter = NetworkAdapter(model, this);
}

void Computer::getAdapter() 
{
	computerNetworkAdapter.getModel();
}

void Computer::toggleAdapter()
{
	if (computerNetworkAdapter.checkStatus() == true)
	{
		computerNetworkAdapter.disable();
	}
	else
	{
		computerNetworkAdapter.enable();
	}
}

void Computer::checkAdapter()
{
	cout << "The network adapter is ";
	if (computerNetworkAdapter.checkStatus())
	{
		cout << "On" << endl;
	}
	else
	{
		cout << "Off" << endl;
	}
}

void Computer::setUSBhub(int x, string set_model)
{
	computerUSBhub = USB_hub(x, this);
	computerUSBhub.setModel(set_model);
}

void Computer::enableHub()
{
	computerUSBhub.enableAll();
}

void Computer::disableHub()
{
	computerUSBhub.disableAll();
}

void Computer::checkHub()
{
	computerUSBhub.checkAll();
}

USB_hub* Computer::accessHub()
{
	return &computerUSBhub;
}

void Computer::setDrive(string model, bool state, int set_space, string ID)
{
	computerDrive.set_installedOn(this);
	computerDrive.setModel(model);
	computerDrive.setState(state);
	computerDrive.setSpace(set_space);
	computerDrive.setID(ID);
}

Harddrive* Computer::getDrive()
{
	return &computerDrive;
}

void Computer::insert(USB_Drive* drive)
{
	computerUSBhub.insert(drive, this);
	
	if (computerOS.getAutorun())
	{
		computerUSBhub.getLatest()->autorun();
	}
}

void Computer::eject(USB_Drive* drive)
{
	computerUSBhub.eject(drive, drive->getID());
}

NetworkAdapter* Computer::getNetworkAdapter()
{
	return &computerNetworkAdapter;
}

EthernetPort* Computer::getEthernetPort()
{
	return &computerEthernetPort;
}

void Computer::addUser(User newUser, string username)
{
	computerOS.addUser(newUser, username);
}

void Computer::removeUser(string username)
{
	computerOS.removeUser(username);
}

void Computer::connect(Connection* new_connect)
{
	computerNetworkAdapter.connect(new_connect);
}

void Computer::disconnect(Connection* end_connect)
{
	computerNetworkAdapter.disconnect(end_connect);
}

void Computer::plugInEthernet(Connection* new_connect)
{
	computerEthernetPort.connect(new_connect);
}

void Computer::unplugEthernet(Connection* end_connect)
{
	computerEthernetPort.disconnect(end_connect);
}