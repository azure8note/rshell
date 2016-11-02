#include "Or.h"

// Returns leftCmd ptr
Base* Or::getLeftCmd() const {
	return leftCmd;
}

// Returns rightCmd ptr
Base* Or::getRightCmd() const {
	return rightCmd;
}

// Returns this->cmdStatus
bool Or::getCmdStatus() const {
	return cmdStatus;
}


// Sets leftCmd to Base* parameter leftCmd
void Or::setLeftCmd(Base* leftCmd) {
	this->leftCmd = leftCmd;
}

// Sets rightCmd to Base* parameter rightCmd
void Or::setRightCmd(Base* rightCmd) {
	this->rightCmd = rightCmd;}
}

// Sets cmdStatus to bool value passed in
void Or::setCmdStatus(bool stat) {
	this->cmdStatus = stat;
}

/* Calls leftCmd's execute(). If leftCmd executed
   successfully, calls rightCmd's execute()
*/
void Or::execute() {
	if (leftCmd->getCmd() != '\0') { // Checks if leftCmd is a dummy cmd
		leftCmd->execute(); // If not a dummy cmd, execute
	} 
 
	if(leftCmd->getCmdStatus()) { 
		rightCmd->execute();
		setCmdStatus(true); // Sets this->cmdStatus to true
	} else {
		setCmdStatus(false); // Sets this->cmdStatus to false
	}
}
