#include "CmdComposite.h"
#include "SingleCmd.h"
#include "MultiCmd.h"

void CmdComposite::addCmd(char* cmd) {
	if (cmd->find("&&") != string::npos || cmd->find("||") != string::npos)
	{
		cmdList.push_back(new SingleCmd(*cmd));
	} else {
		cmdList.push_back(new MultiCmd(*cmd));
	}

	return;
}

void CmdComposite::parse(int argc, char* argv[]) {
	//string cmdLine = readCmd();
	string cmdLine = "";
	char* tokptr; //Token ptr

	for (int i = 0; i < argc; ++i) {
		cmdLine += argv[i];
		
	}	
	
	// Set tokptr to beginning of first token
	tokptr = strtok(cmdLine, ";"); // Tokens split by ; can be single or multi commands
	while (tokptr != NULL) {
		addCmd(tokptr);
		tokptr = strtok(NULL, ";"); // Continue scanning where prev successful call ended
	}

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
