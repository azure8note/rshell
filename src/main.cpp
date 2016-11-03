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
		cout << usrname  << "@" << hostname << " $ ";
		getline(cin, cmdLine, '\n');
		cmdList->parse(cmdLine);
		cmdList->execute(); // exit command is checked for in execute()		
		cin.clear();
	}  
	return 0;
}
