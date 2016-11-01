#include "Base.h"
#include "SingleCmd.h"
#include "MultiCmd.h"
#include "CmdComposite.h"

#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	
    bool flag = true;
    char hostname[128];
    char* usrname = getlogin();
    gethostname(hostname, sizeof hostname);
   
    while (flag){
	cout << usrname  << "@" << hostname << "$ ";
	CmdComposite* cmdLine = new CmdComposite();
	cmdLine->parse(argc, argv);
	cmdLine->execute();
	
	//if (exit) {
	  //flag = false;
	//}
	flag = false;
   }
  
  
  
	
	return 0;
}
