#include "CmdComposite.h"
#include "SingleCmd.h"
#include "MultiCmd.h"

void CmdComposite::addCmd(char* cmd) {
	string cmdCpy(cmd);
	if (cmdCpy.find("&&") != string::npos ||
	    cmdCpy.find("||") != string::npos) {
		cmdList.push_back(new SingleCmd(cmd));
	} else {
		cmdList.push_back(new MultiCmd(cmd));
	}

	return;
}

void CmdComposite::parse(int argc, char* argv[]) {
	//string cmdLine = readCmd();
	string cmdLine = "";

	for (int i = 0; i < argc; ++i) {
		cmdLine += argv[i];
	}	

	char* cstr = new char [cmdLine.length() + 1];
	strcpy(cstr, cmdLine.c_str()); // cstr now contain c-string copy of cmdLine
	
	// Set tokptr to beginning of first token
	char* tokptr = strtok(cstr, ";"); // Tokens split by ; can be single or multi commands
	while (tokptr != NULL) {
		addCmd(tokptr);
		tokptr = strtok(NULL, ";"); // Continue scanning where prev successful call ended
	}
	delete[] cstr; // De-allocate cstr memory
	return;
}

void CmdComposite::execute() {
	for (unsigned int i = 0; i < cmdList.size(); ++i) {
		cmdList.at(i)->execute();
	}
	return;
}

Base* CmdComposite::getCmd(int a) {
	return cmdList.at(a);
}
