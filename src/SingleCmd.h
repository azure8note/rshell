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
	bool cmdStatus; // for the multi command calls
	char* args[64]; // for additional flags and arguments passed into the single commands

public:
	//CONSTRUCTORS
	SingleCmd() : Base() {
	  cmd = '\0';
	  cmdStatus = true;
	};
	SingleCmd(char* str) : Base() {
	  cmd = str;
	  cmdStatus = true;
	};

	//Accessors and Mutators
	void setCmd(char* str);
	char* getCmd() const;
	void setStatus(bool b);
	bool getStatus() const;

	//The main function used by the composite pattern
	void parse();//used by the execute to remove spaces
	void execute();
};

#endif
