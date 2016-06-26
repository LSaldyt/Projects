#include "stdafx.h"
#include "Computer.hpp"
#include "Software.hpp"
#include "WirelessNetworkAdapter.hpp"
#include "USBHub.hpp"
#include "StorageDevice.hpp"
#include "USB_Drive.hpp"
#include "User.hpp"
#include "Virus.hpp"
#include "Antivirus.hpp"
#include "Connection.hpp"
#include "Browser.hpp"
#include "Website.hpp"
#include "Router.hpp"


int main()
	{
		{ //Virtual block for testing both Network and USB related viruses at the same time!!!!
		
			cout << "\n\n\n Maclab Simulation? \n\n\n";

			//#Kill the maclab
			OperatingSystem OSX;
			OSX.setAutorun(true);
		
			int mac_amount;
			cout << "How many macs do you desire?" << endl;
			std::cin >> mac_amount;

			vector<Computer*> macs;

			for (int i = 0; i < mac_amount; i++)
			{
				macs.push_back(new Computer(OSX));
			}
			Router labRouter;
			//The addition of a router object makes all processesses O(n) at worst :)


			for (int i = 0; i < macs.size(); i++)
			{
					macs[i]->getNetworkAdapter()->getConnection()->connect(labRouter.getConnection());
			}

			USB_Drive Regret_32_gb(32, "Regret_32_gb");
			Virus NoViCe("NoViCe", "1.12.155");
			cout << NoViCe.getName() << endl;
			Regret_32_gb.Install(&NoViCe, "default", NULL);

			int host = rand() % macs.size() + 1;
			macs[host]->insert(&Regret_32_gb);

			cout << "\n\n\n End Maclab simulation \n\n\n";

		}
	return 0;
}


/*
//Removed the hardware/software test block in this version

cout << "\n\n\n Virus Test 1: \n\n\n" << endl;

//-------------------------------------------------------------------------------------------------------//

//Everything past here is a test of a very basic virus//

//-------------------------------------------------------------------------------------------------------//

{ //Virtual Block
OperatingSystem Windows;
Windows.setAutorun(true); //:)

Computer Toshiba_C70(Windows);

Toshiba_C70.start();

Computer ASUS_7786(Windows);

ASUS_7786.start();

//Create two identical computers with different models. Sadly these users are unaware that their version of windows enables autorun

USB_Drive Regret_32_gb; //a full 32 Gigabytes of your regret :)
Regret_32_gb.setModel("All your woes, too");
Regret_32_gb.setSpace(32);

Virus BaSiC;
BaSiC.setName("BaSiC");

//Create an infected USB_Drive
Regret_32_gb.Install(&BaSiC, "default", NULL); //NULL refers to the computer that the virus is installed on

Toshiba_C70.insert(&Regret_32_gb); //Here the NULL pointer gets changed to the Toshiba Machine (hopefully)


There is error handling to check if the InstalledOn pointer doesn't get initialized, but if it doesn't,
then the virus wont spread onto the computers harddrive :(


Toshiba_C70.eject(&Regret_32_gb);

USB_Drive Lexar_16_gb; //A flash drive for the virus to spread onto
Lexar_16_gb.setSpace(16);
Lexar_16_gb.setModel("Lexar_16_gb");

ASUS_7786.insert(&Lexar_16_gb);
ASUS_7786.insert(&Regret_32_gb);
//Now both drives should be infected?

cout << "Both drives infected?" << endl;

ASUS_7786.eject(&Lexar_16_gb);
ASUS_7786.eject(&Regret_32_gb);

cout << "\n-Testing Between Toshiba and ASUS Completed-\n" << endl;

//Just to test that they were:
Computer UnsuspectingSchoolNetwork(Windows);

UnsuspectingSchoolNetwork.start();

UnsuspectingSchoolNetwork.insert(&Lexar_16_gb);
//Inserting the flash drive that got infected by the other
UnsuspectingSchoolNetwork.eject(&Lexar_16_gb);

USB_Drive Lexar_16_gb_2; //Create a third USB Drive (Tricky because the name is so close, though..)
Lexar_16_gb_2.setSpace(16);
Lexar_16_gb_2.setModel("Lexar_16_gb_2");

UnsuspectingSchoolNetwork.insert(&Lexar_16_gb_2); //This drive is clean, so autorun causes nothing
UnsuspectingSchoolNetwork.open("default", "BaSiC"); //If the virus is opened, however... ...
UnsuspectingSchoolNetwork.eject(&Lexar_16_gb_2); //The drive should now be infected

cout << "\n-Testing for School Network Completed-\n" << endl;

Computer LargeCompany(Windows);

LargeCompany.start();

LargeCompany.insert(&Lexar_16_gb_2); //Insert the third drive that the School Network infected
//Hope for the best
LargeCompany.eject(&Lexar_16_gb_2);

Toshiba_C70.shutdown();
ASUS_7786.shutdown();
UnsuspectingSchoolNetwork.shutdown();
LargeCompany.shutdown();

cout << "\n-All USB_Drive testing Completed-\n" << endl;

}
//--------------------------------------------------------------------------------------------------------------------//
//Testing for Network viruses
//--------------------------------------------------------------------------------------------------------------------//
{ //New Virtual Block. All resources from previous test have been deleted!

cout << "\n\n\n\n -Beginning Network Adapter/Ethernet testing- \n\n\n\n" << endl;

cout << "Note: IP's are really just ID numbers in this scenario\n\n";

OperatingSystem Windows; //Valid because of the virtual block(s) above

Computer AlienWare_3000(Windows);
Computer Lenovo_ThinkPad(Windows);

AlienWare_3000.connect(Lenovo_ThinkPad.getNetworkAdapter()->getConnection());
AlienWare_3000.disconnect(Lenovo_ThinkPad.getNetworkAdapter()->getConnection());
//Probably going to write some other way to handle this, but this is just to test if the functions work,
//so the way that each function gets called doesn't really matter

AlienWare_3000.plugInEthernet(Lenovo_ThinkPad.getEthernetPort()->getConnection());
AlienWare_3000.unplugEthernet(Lenovo_ThinkPad.getEthernetPort()->getConnection());

//Interestingly, this should work (maybe):
AlienWare_3000.connect(Lenovo_ThinkPad.getNetworkAdapter()->getConnection());
Lenovo_ThinkPad.disconnect(AlienWare_3000.getNetworkAdapter()->getConnection());

AlienWare_3000.shutdown();
Lenovo_ThinkPad.shutdown();

AlienWare_3000.start();
Lenovo_ThinkPad.start();

Virus BaSiC; //Recreate our virus object
BaSiC.setName("BaSiC");

cout << "Virus Created" << endl;

Lenovo_ThinkPad.connect(AlienWare_3000.getNetworkAdapter()->getConnection());
int Alien_IP = AlienWare_3000.getNetworkAdapter()->getConnection()->getIP();

Lenovo_ThinkPad.getNetworkAdapter()->getConnection()->getConnect(Alien_IP)->giveAccess()->Install(&BaSiC, "default");

//Lenovo installs a virus on the Alienware because as of now it has complete access over the other device
//This will obviously change once a permission system gets added in
//And also possibly if you want this to better mimic the actual process of sending data over two computers

//Also, technically the function *could* look like:
//(Except this is the Alienware spreading the virus back to the Lenovo)

AlienWare_3000.getNetworkAdapter()->getConnection()->getConnect(Lenovo_ThinkPad.getNetworkAdapter()->getConnection()->getIP())->giveAccess()->Install(&BaSiC, "default");

// :)
//Luckily I'm planning on masking all of this stuff in the near future
//First off the above line should be inside of the virus class, but with pointer to computers instead, since this can be made polymorphic

So, the Idea being that a Virus could scan the active connections of its host computer, and then try and install itself to them
I know this isn't an entirely accurate replica of the process that *actually* happens over a network, but its enough to begin running
some tests. Anyways..



//Alright, I'm going to leave the tests above because I feel like they show the functionality a  little more than the code I wrote in Virus.cpp,
//But here is how that works:

Computer Dell_99; //Now these are auto-instantiated
Computer HP_mini;

//Create two clean computers

Dell_99.connect(HP_mini.getNetworkAdapter()->getConnection());
HP_mini.connect(AlienWare_3000.getNetworkAdapter()->getConnection()); //This computer connects to the infected alienware

AlienWare_3000.open("default", "BaSiC"); //Virus is triggered
//Virus spreads to the HP_mini, hopefully

cout << "\n\n -Network Testing Completed- \n\n";
}

//Browser/Website Testing virtual block
{
cout << "\n\n\n -Browser/Website Testing: \n\n\n";

Browser Google_Chrome("Chrome", "1.12.11");
OperatingSystem Windows;

Computer Toshiba_C70(Windows);
Computer Toshiba_Satelite(Windows);

Toshiba_C70.Install(Google_Chrome); //Overloaded version of the Install function specific to browsers.
Toshiba_Satelite.Install(Google_Chrome); //Install google chrome on both machines

Website RussianTorrents("torrentbus.com");
Website Microsoft("microsoft.com");

Virus BaSiC("BaSiC", "1.2.1");
Software MicrosoftWord("MS_Word", "2014");

RussianTorrents.upload(&BaSiC);
Microsoft.upload(&MicrosoftWord);

Toshiba_C70.getBrowser()->goTo("microsoft.com");
Toshiba_Satelite.getBrowser()->goTo("torrentbus.com");

Toshiba_C70.getBrowser()->download("MS_Word");
Toshiba_Satelite.getBrowser()->download("BaSiC"); //This took literally three hours of debugging to get to x)

cout << "\n\n\n -Browser/Website Testing completed- \n\n\n";
}
*/