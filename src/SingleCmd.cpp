#include "SingleCmd.h"
//setters and getters --------------
void SingleCmd::setCmd(char* str){
	cmd = str;
	return;
}

char* SingleCmd::getCmd() const{
	return cmd;
}

bool SingleCmd::getCmdStatus() const{
  return cmdStatus;
}

void SingleCmd::setCmdStatus(bool b){
  cmdStatus = b;
}
//----------------------------------

void SingleCmd::parse() {// seperates the command from its flag into two seperate tokens
  
  char* tok;
  
	if(cmd[0] == ' '){ // if there is a space after the ';' this removes it
		string cmdCpy(cmd);
		cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
		char* cstr = new char[cmdCpy.length()+1];
		strcpy(cstr, cmdCpy.c_str());
		cmd = cstr;
	}
  

	tok = strtok(cmd, " "); //first seperation
	args[0] = tok;
  
	for (unsigned i = 1; tok != NULL ; i++){ //assigns the tokens into args
	  tok = strtok(NULL, " ");
	  args[i] = tok;
    }
}

void SingleCmd::execute() {
  
  this->parse(); //makes the function readable
  
  string lowE = "exit";
  string capE = "EXIT";
 
  if (args[0] == lowE.c_str() || args[0] == capE.c_str()){ // checks exit case
    exit(0);
  }

  	pid_t pid; //for the forking
  	int status; //for the waiting
  
	pid = fork(); // fork fro child process
  
	if (pid < 0) { /*fork a child process*/
	   	 perror("fork");// didn't fork properly
	} 
	else if(pid == 0){ //child processs
	  	if (execvp(args[0], args) < 0){// calls execute
			setStatus(false);//in case it fails changes the status (for multi comand
			perror ("exec"); //error checks
	  	}	
	}
	else {//parent
  		pid_t wpid; // waits for child to finish
	  	do {
	    		wpid = waitpid(pid, &status, WUNTRACED);
	  	}
	  	while(wpid <= -1);
	}
}
