#ifndef CMDCOMP_H
#define CMDCOMP_H
#include "Base.h"

#include <stddef.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>


using std::vector;
using std::string;

class CmdComposite : public Base {
private:
	vector <Base*> cmdList;	
	
public:
	//Constructor
	CmdComposite() : Base() {};
	
	void parse(string cmdLine);
	void addCmd(char* cmd);
	void execute();

	//Accessor
	Base* getCmd(int a) const;
	//Mutator
	void clearCmds();
	
};

#endif
