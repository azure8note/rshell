#include "MultiCmd.h"

void MultiCmd::changeCmd(string str){
	cmdString = str;
	return;
}

string MultiCmd::readCmd() {
	return cmdString;
}

void MultiCmd::changeStatus() {
	if (cmdStatus){
		cmdStatus = false;
	} 
	else {
		cmdStatus = true;
	}
}

bool MultiCmd::getStatus() {
	return cmdStatus;
}

void MultiCmd::execute() {
	//FIXME NEEDS TO BE DONE
}