#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include "Hardware.hpp"

class Processor : public Hardware
{
protected:
	//Just some examples of what data might be included in the class
	int cores;
	float processorSpeed;

public:
	void CreateProcessor(string set_model, int set_cores, float set_processorSpeed);
	float ReturnProcessorSpeed(int CPUThreads);
	void ReturnProcessor();
	void Init();

	~Processor() {};
	Processor();
	Processor(string, int, float);
};

#endif

