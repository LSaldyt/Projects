#include "stdafx.h"

#ifndef PERMISSIONS_HPP
#define PERMISSIONS_HPP
class Computer;

class Permissions
{
protected:
	int level; //probably some kind of enum would be cool, that way "ADMIN", for example, would evaluate to 1
	Computer *accessOn; //The machine that this piece of software is allowed to access at its permission level


	// Personally I think
	/*
	
	//On windows, this is the system of permissions used: (I understand that it's diferent on unix based systems)

	Read -Permits viewing and listing of files and subfolders  -Permits viewing or accessing of the file's contents

	Write -Permits adding of files and subfolders  -Permits writing to a file

	Read & Execute  -Permits viewing and listing of files and subfolders as well as executing of files; inherited by files and folders  -Permits viewing and accessing of the file's contents as well as executing of the file

	List Folder Contents  -Permits viewing and listing of files and subfolders as well as executing of files; inherited by folders only  -N/A

	Modify  -Permits reading and writing of files and subfolders; allows deletion of the folder  -Permits reading and writing of the file; allows deletion of the file

	Full Control  -Permits reading, writing, changing, and deleting of files and subfolders  -Permits reading, writing, changing and deleting of the file
	
	https://msdn.microsoft.com/en-us/library/bb727008.aspx

	*/
	
	// 0 need to be no access. 1 - 7 needs to be universal write/ read/ execute (as per unix numeric notation) if we want to assign permissions to folders. 8 can be normal user, 9 admin, and 10 system.
	// We can assign permissions to both users and folders
	// In general we can avoid actual files, simply folders like "System Dir" "User Dir" etc. If it has read access we can assume the subdirs do too. This is of course with the exception of Appdata
	// Which should get it's own permissions of read only.

public:
	Permissions();
	~Permissions();
	//whatever you feel like needs to be added

	void setAccessOn(Computer*);
};

#endif
