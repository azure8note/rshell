#ifndef SINGLECMD_H
#define SINGLECMD_H
#include "Base.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using std::string;

class SingleCmd: public Base {

private:
	char* cmd;

public:
	//CONSTRUCTORS
	SingleCmd() : Base() {};
	SingleCmd(char* str) : Base(), cmd(str) {};

	//Accessors and Mutators
	void changeCmd(string str);
	char* readCmd();

	//The main function used by the composite pattern
	void execute();
};

#endif
