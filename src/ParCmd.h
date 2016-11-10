#ifndef PARCMD_H //FOR NOW NOT BEING USED
#define PARCMD_H

#include "Base.h"
#include "MultiCmd.h"

class ParCmd : public Base {
    private:
	char* cmdString;
	vector<MultiCmd*> cmds;
	
    public:
	ParCmd () : Base() {}
	ParCmd (char* str) : Base() {
	    cmdString = str;
	}
	void parse(); 
	void execute();
};

#endif
