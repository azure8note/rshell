#ifndef MULTICMD_H
#define MULTICMD_H
#include "Base.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using std::string;

class MultiCmd: public Base {

private:
	char* cmdString;
	bool cmdStatus;

public:
	//CONSTRUCTORS
	MultiCmd() : Base() {};
	MultiCmd(char* str) : Base(), cmdString(str) {};

	//Accessors and Mutators
	void changeCmd(string str);
	char* readCmd();
	void changeStatus();
	bool getStatus();

	//The main function used by the composite pattern
	void execute();//LOOK AT CCP FILE IT STILL NEEDS TO BE DONE
};

#endif