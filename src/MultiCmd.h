#ifndef MULTICMD_H
#define MULTICMD_H
#include "Base.h"
#include "And.h"
#include "Or.h"
#include "SingleCmd.h"
#include "Base.h"

#include <iostream> //cout cerr
#include <stddef.h> //NULL
#include <string> //for strings 
#include <cstring> //for cstrings
#include <stdlib.h> 
#include <queue> //que of commands
#include <vector> //vector of comands
#include <stdexcept> //for the error output

using std::queue;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cerr;

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
	   cmdStatus = false;
	};
	MultiCmd(char* str) : Base() {
	  cmdString = str;
	  cmdStatus = false;
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
