#ifndef CMDCOMP_H
#define CMDCOMP_H
#include "Base.h"
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

class CmdComposite : public Base {
private:
	vector <Base*> cmdList;
	//Constructor
	CmdComposite() : Base() {};
	
public:
	void readCmd(int argc, char* argv[]);
	void parse(int arc, char* argv[]);
	void addCmd(string cmd);
	void execute();

//Accessor and Mutator
	Base* getCmd(int a);
};

#endif