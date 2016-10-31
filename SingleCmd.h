#ifndef SINGLECMD_H
#define SINGLECMD_H
#include "Base.h"
#include <string>

using std::string;

class SingleCmd: public Base {

private:
	string cmd;

public:
	//CONSTRUCTORS
	SingleCmd() : Base() {};
	SingleCmd(string str) : Base(), cmd(str) {};

	//Accessors and Mutators
	void changeCmd(string str);
	string readCmd();

	//The main function used by the composite pattern
	void execute(); //LOOK AT CCP FILE IT STILL NEEDS TO BE DONE
};

#endif
