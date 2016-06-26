// Computer.hpp : Defines the entry point for the console application.
//
#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include "Processor.hpp"
#include "Software.hpp"
#include "WirelessNetworkAdapter.hpp"
#include "USBHub.hpp"
#include "Harddrive.hpp"
#include "WirelessNetworkAdapter.hpp"
#include "OperatingSystem.hpp"
#include "EthernetPort.hpp"
#include "Browser.hpp"

//A really basic outline for a computer object that is obviously going to change as we add other objects

class Computer // Base Class for any computer in the network
{
protected:
	Processor computerProcessor;
	NetworkAdapter computerNetworkAdapter;
	USB_hub computerUSBhub;
	Harddrive computerDrive;
	EthernetPort computerEthernetPort;
	Browser browser;
	Processor computerCPU; //I went ahead and made this protected for you

	OperatingSystem computerOS; // Contains the User objects etc

	bool on;

	double timeSteps; // amount of computer time in seconds tracked on each machine.

public:

	Computer();
	Computer(OperatingSystem);
	~Computer();

	void start();
	void login(string user, string pass);
	void logout(string);
	void restart();
	void shutdown();


	void Computer::ConstructProcessor(float cpuSpeed, int cpuCores);
	string Computer::GenerateCorporateNameUsingUser();


	void addUser(User, string);
	void removeUser(string);

	void checkOn();

	void InstallOS(OperatingSystem);

	void Install(Software*, string);
	void Install(Browser);

	Software* open(string, string);
	void close(string, string);
	void checkSoftware(string, string);

	void setProcessor(string model, int cores, float speed);
	float getProcessorSpeed(int CPUThreads);
	void getProcessor();

	void setDrive(string, bool, int, string);
	Harddrive* getDrive();

	void setAdapter(string model);
	void checkAdapter();
	void toggleAdapter();
	void getAdapter();

	void setUSBhub(int, string);
	void enableHub();
	void disableHub();
	void checkHub();
	USB_hub* accessHub();

	void insert(USB_Drive*);
	void eject(USB_Drive*);

	void plugInEthernet(Connection*);
	void unplugEthernet(Connection*);

	void connect(Connection*);
	void disconnect(Connection*);
	
	NetworkAdapter* getNetworkAdapter();
	EthernetPort* getEthernetPort();
	Browser* getBrowser() { return &browser; };
};

#endif
