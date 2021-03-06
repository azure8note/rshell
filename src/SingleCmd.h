#ifndef SINGLECMD_H
#define SINGLECMD_H
#include "Base.h"
//#include "CdCmd.h"

#include <cstring>
#include <iostream> /* cerr, cout */
#include <stddef.h> /* NULL */
#include <stdio.h> /* perror */
#include <stdlib.h> /* getenv, setenv */
#include <sys/stat.h> /* stat */
#include <sys/types.h> /* stat, pid_t */
#include <sys/wait.h> /* waitpid */
#include <unistd.h> /* access, chdir, execvp, fork, stat */

using std::cout;
using std::endl;
using std::string;

class SingleCmd: public Base {

private:
	char* cmd;
	bool cmdStatus; // For the multi command calls
	char* args[64]; // For additional flags and arguments passed into the single commands

public:
	/* Constructors */
	SingleCmd() : Base() {
		cmd = '\0';
		cmdStatus = true; // Need to be true since once execvp executes, cmdStatus cannot be updated
	}

	SingleCmd(char* str) : Base() {
		cmd = str;
		cmdStatus = true;
	}

	/* Accessors and Mutators */
	char* getCmd() const;
	bool getCmdStatus() const;
	void setCmd(char* str);
	void setCmdStatus(bool b);

	void parse(); // Used by the execute to remove spaces
	void execute();

	/* Helper Functions */
	string parseCd(string cwd); 
	void executeCd(); // Calls the cd command execute if cd is in the command
	void executeTest(); // Calls the test command execute if test is in the command
};

#endif
