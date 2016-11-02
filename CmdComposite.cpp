#include "CmdComposite.h"
#include "SingleCmd.h"
#include "MultiCmd.h"

void CmdComposite::addCmd(char* cmd) {
	string cmdCpy(cmd); // Create string of cmd
	if (cmdCpy.find("&&") != string::npos ||
	    cmdCpy.find("||") != string::npos) { // Check for any connectors
		cmdList.push_back(new MultiCmd(cmd)); // Create and pushback MultiCmd
	} else { // No &&, || connectors
		cmdList.push_back(new SingleCmd(cmd)); // Create and pushback SingleCmd
	}

	return;
}

void CmdComposite::parse(string cmdLine) {
	unsigned int pos = cmdLine.find("#"); // Check for comment
	// If comment exists, create substring without commented portion.
	if (pos != string::npos) {
		cmdLine = cmdLine.substr(0, pos);	
	}

	// cstr now contain c-string copy of cmdLine
	char* cstr = new char [cmdLine.length() + 1];
	strcpy(cstr, cmdLine.c_str());
	
	// Set tokptr to beginning of first token
	char* tokptr = strtok(cstr, ";"); // Tokens split by ; can be single or multi commands
	while (tokptr != NULL) {
		addCmd(tokptr);
		tokptr = strtok(NULL, ";"); // Continue scanning where prev successful call ended
	}

	return;
}

/*
 execute() iterates through the cmdList vector, calling
 execute() for the respective SingleCmd or MultiCmd
*/
void CmdComposite::execute() {
	for (unsigned int i = 0; i < cmdList.size(); ++i) {
		cmdList.at(i)->execute();
	}
	return;
}

// Returns Base* at int a
Base* CmdComposite::getCmd(int a) const {
	return cmdList.at(a);
}
