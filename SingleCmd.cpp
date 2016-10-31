#include "SingleCmd.h"

void SingleCmd::changeCmd(string str){
	cmd = str;
	return;
}

string SingleCmd::readCmd() {
	return cmd;
}

void SingleCmd::execute() {
	char* command = cmd.c_str();
	if (command[0] == "#"){
		return;
	}
	if (execl(/*PATH "/bin/" ?*/, command, NULL) < 0){//? idk if this works
		cout << "ERROR EXECUTING";
	}
}
