#ifndef AND_H
#define AND_H

#include "Base.h"
#include <stddef>

class And : public Base {
	private:
		Base* leftCmd;
		Base* rightCmd;
		
	public:
		// Constructor
		And() : Base(), leftCmd(NULL), rightCmd(NULL) {};

		// Accessors for left and right command ptrs
		Base* getLeftCmd();
		Base* getRightCmd();
		
		// Mutators for left and right 
		void setLeftCmd(Base* leftCmd);
		void setRightCmd(Base* rightCmd);
		
		// Calls execute 
		void execute();
};

#endif
