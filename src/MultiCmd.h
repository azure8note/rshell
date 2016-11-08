#ifndef MULTICMD_H
#define MULTICMD_H
#include "Base.h"
#include "And.h"
#include "Or.h"
#include "SingleCmd.h"
#include "Base.h"

#include <iostream>
#include <stddef.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>
#include <queue>
#include <vector>
#include <stdexcept>

using std::queue;
using std::string;
using std::cout;
using std::endl;
using std::vector;


class MultiCmd: public Base {

private:
	char* cmdString; // string of multi commands
	bool cmdStatus;  // used for checking connector cases
	queue<Base*> cmdQueue; // used for the output
	vector<char*> cmds; // holds the commands after being parsed
public:
	//CONSTRUCTORS
	MultiCmd() : Base() {
	  *cmdString = '\0';
	};
	MultiCmd(char* str) : Base() {
	  cmdString = str;
	}
	
	//Accessors and Mutators
	void setCmd(char* str);
	char* getCmd() const;
	void setCmdStatus(bool b);
	bool getCmdStatus() const;
	
	
	void makeQueue();// makes queue to be used for execute
	void parse(); // used for execute to split the cmdstring into cmds and connectors
	

	//The main function used by the composite pattern
	void execute();
};

#endif
