#ifndef MULTICMD_H
#define MULTICMD_H
#include "Base.h"
#include "And.h"
#include "Or.h"
#include "SingleCmd.h"

#include <iostream>
#include <stddef.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>
#include <queue>
#include <vector>

using std::stack
using std::string;
using std::cout;
using std::endl;


class MultiCmd: public Base {

private:
	char* cmdString;
	bool cmdStatus;
	queue<Base*> cmdQueue;
	vector<char*> Cmds;
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
	void setStatus(bool b);
	bool getStatus() const;
	void makeQueue();
	void parse();
	

	//The main function used by the composite pattern
	void execute();
};

#endif
