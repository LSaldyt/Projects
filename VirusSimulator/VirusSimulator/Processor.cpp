#include "stdafx.h"
#include "Processor.hpp"

void Processor::CreateProcessor(string set_model, int set_cores, float set_processorSpeed)
{
	//Why use the "this" operator?
	model = set_model;
	cores = set_cores;
	processorSpeed = set_processorSpeed;
}



//This returns the proc speed in GHZ given a known number of threads
float Processor::ReturnProcessorSpeed(int CPUThreads) {

	if (CPUThreads > cores) {
		CPUThreads = cores;//Stops it from running faster than computer can manage
	}

	float procSpeed = CPUThreads * processorSpeed; //calculates effective action speed

	return procSpeed;
}

void Processor::ReturnProcessor()
{
	// "Return"
	cout << "Processor Info: " << endl;
	cout << "Model: " << model << endl;
	cout << "Cores: " << cores << endl;
	cout << "Processor Speed: " << processorSpeed << endl;
}

Processor::Processor() 
{
	Init();

}

void Processor::Init()
{
	model = "";
	cores = 0;
	processorSpeed = 0;
}


Processor::Processor(string set_model, int set_cores, float speed)
{
	model = set_model;
	cores = set_cores;
	processorSpeed = speed; //We might want a multiplier here to account for more modern CPU technologies. IDK.
	//Sure, but only if it seems like its relevant to the viruses? (Which it might not be?)
	//Theres definitely no harm in adding it though
}



