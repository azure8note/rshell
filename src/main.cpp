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
	//cout << usrname  << "@" << hostname << " $ ";
	
	string cmdLine = "";
	CmdComposite* cmdList = new CmdComposite();
	/*getline(cin, cmdLine);	
	cmdList->parse(cmdLine);
	cmdList->execute();*/
		
	while(1) {
		string cmdLine2 = "";
		string path(getenv(PATH); // Removes the redundant part of the path
		int index = 0;
		
		for (unsigned i = 0; i < path.size(); i++){
		    if (path.at(i) = '/'){
		       int counter++;
		    }
		    if (counter == 2) {
		      index = i;
		      break;
		    }
		}
		
		if (index != 0){
		    path = path.substr(index, path.length() - index);
		}
		
		cout << usrname  << "@" << hostname << ":~/" << path << " $ ";
		getline(cin, cmdLine);
		cmdList->parse(cmdLine);
		cmdList->execute(); // exit command is checked for in execute()
		cmdList->clearCmds();
	}  
	return 0;
}
