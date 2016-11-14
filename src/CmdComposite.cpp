#include "CmdComposite.h"
#include "SingleCmd.h"
#include "MultiCmd.h"
#include "ParCmd.h"

using std::cerr;

void CmdComposite::clearCmds() {
	cmdList.clear();
}

void CmdComposite::addCmd(char* cmd) {
	string cmdCpy(cmd); // Create string of cmd
	if (cmdCpy.find("&&") == 0 || cmdCpy.find("||") == 0) {
		throw "INVALID INPUT: CANNOT BEGIN COMMAND WITH CONNECTOR";
	}
	if (cmdCpy.find("&&") != string::npos ||
	    cmdCpy.find("||") != string::npos) { // Check for && or || connectors
		int numOpen = 0; // Number of opening parentheses
		int numClose = 0; // Number of closing parentheses
		for (int i = 0; i < cmdCpy.size(); ++i) {	
			if (cmdCpy.find("(") != string::npos) {
				++numOpen;
			}
			if (cmdCpy.find(")") != string::npos) {
				++numClose;
			}
		}		
		if (numOpen != numClose) { // If no closing parentheses is found, throw Invalid 
			throw "INVALID INPUT: NO CLOSING PARENTHESES";
		} else if (numOpen) {
			cmdList.push_back(new MultiCmd(cmd, true));
		}
		
		cmdList.push_back(new MultiCmd(cmd)); // Create and pushback MultiCmd
	} else { // No && or || connectors in string
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
		try {
			addCmd(tokptr);
		} catch (const char* error_msg) {
			cerr << error_msg << endl;
		}
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
