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

	char* cmd;
	cmd = strtok(cmdString.c_str(), " ");
	
	while (cmd != NULL) {

		if(cmd[0] == "#"){ //comment case
			return;
		}
		else if( *cmd == "&&" && cmdStatus){// && case
			if (execvp(/*PATH "/bin/" ?*/, cmd, NULL) < 0){//? idk if this works
				cmdStatus = false;
				out << "ERROR EXECUTING" << endl;
			}
			else {
				cmdStatus = true;
				cmd = strtok(NULL, " ");
			}
		}
		else if ( *cmd == "||" && !cmdStatus){ // || case
			if (execvp(/*PATH "/bin/" ?*/, cmd, NULL) < 0){//? idk if this works
				cmdStatus = false;
				out << "ERROR EXECUTING" << endl;
			}
			else {
				cmdStatus = true;
				cmd = strtok(NULL, " ");
			}
		}
		else if (execvp(/*PATH "/bin/" ?*/, cmd, NULL) < 0){//? idk if this works //general case
			cmdStatus = false;
			cout << "ERROR EXECUTING" << endl;
		}
		else {
				cmdStatus = true;
				cmd = strtok(NULL, " ");
		}
	}
}