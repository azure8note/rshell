#ifndef MULTICMD_H
#define MULTICMD_H
#include "Base.h"
#include <string>

using std::string;

class MultiCmd: public Base {

private:
	string cmdString;
	bool cmdStatus;

public:
	//CONSTRUCTORS
	MultiCmd() : Base() {};
	MultiCmd(string str) : Base(), cmdString(str) {};

	//Accessors and Mutators
	void changeCmd(string str);
	string readCmd();
	void changeStatus();
	bool getStatus();

	//The main function used by the composite pattern
	void execute();//LOOK AT CCP FILE IT STILL NEEDS TO BE DONE
};

#endif