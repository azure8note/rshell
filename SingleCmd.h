#ifndef SINGLECMD_H
#define SINGLECMD_H
#include "Base.h"

#include <stddef.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>

using std::string;
using std::cout;
using std::endl;

class SingleCmd: public Base {

private:
	char* cmd;

public:
	//CONSTRUCTORS
	SingleCmd() : Base() {};
	SingleCmd(char* str) : Base(), cmd(str) {};

	//Accessors and Mutators
	void changeCmd(char* str);
	char* readCmd();

	//The main function used by the composite pattern
	void execute();
};

#endif
