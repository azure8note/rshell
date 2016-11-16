#ifndef SINGLECMD_H
#define SINGLECMD_H
#include "Base.h"

#include <cstring>
#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

class SingleCmd: public Base {

private:
	char* cmd;
	bool cmdStatus; // for the multi command calls
	char* args[64]; // for additional flags and arguments passed into the single commands

public:
	//CONSTRUCTORS
	SingleCmd() : Base() {
	  cmd = '\0';
	  cmdStatus = true; // needs to be set true since once execvp executes we cant change the status of it
	};
	SingleCmd(char* str) : Base() {
	  cmd = str;
	  cmdStatus = true;
	};

	//Accessors and Mutators
	void setCmd(char* str);
	char* getCmd() const;
	void setCmdStatus(bool b);
	bool getCmdStatus() const;

	//The main function used by the composite pattern
	void parse();//used by the execute to remove spaces
	void execute();
};

#endif
