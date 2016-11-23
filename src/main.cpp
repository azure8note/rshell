#include "Base.h"
#include "SingleCmd.h"
#include "MultiCmd.h"
#include "CmdComposite.h"

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <limits.h>
#include <stdlib.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
	//bool flag = true;
	char hostname[256];
	char* usrname = getlogin();
	gethostname(hostname, sizeof hostname);
    
	cout << "\033c";
	string cmdLine = "";
	CmdComposite* cmdList = new CmdComposite();
	
	while(1) {
		string path(getenv("PWD")); // Removes the redundant part of the path
		
		string user(getenv("USER"));
		unsigned numChar = path.find(user) + user.size();

		path = path.substr(numChar, path.size()-numChar);
		
		cout << usrname  << "@" << hostname << ":~" << path << " $ ";
		getline(cin, cmdLine);
		cmdList->parse(cmdLine);
		cmdList->execute(); // Exit command is checked for in execute()
		cmdList->clearCmds();
	} 
 
	return 0;
}
