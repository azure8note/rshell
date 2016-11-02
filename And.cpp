#include "And.h"

// Returns leftCmd ptr
Base* And::getLeftCmd() {
	return leftCmd;
}

// Returns rightCmd ptr
Base* And::getRightCmd() {
	return rightCmd;
}

// Sets leftCmd to Base* parameter leftCmd
void And::setLeftCmd(Base* leftCmd) {
	this->leftCmd = leftCmd;
}

// Sets rightCmd to Base* parameter rightCmd
void And::setRightCmd(Base* rightCmd) {
	this->rightCmd = rightCmd;}
}

/* Calls leftCmd's execute(). If leftCmd executed
   successfully, calls rightCmd's execute()
*/
void And::execute() {
	leftCmd->execute(); 
	if(leftCmd->getCmdStatus()) { 
		rightCmd->execute();
	}
}

