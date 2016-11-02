#include "MultiCmd.h"

void MultiCmd::changeCmd(char* str){
	cmdString = str;
	return;
}

char* MultiCmd::readCmd() {
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
  
      string an = "&&";
      string o = "||";
  
     if(cmdString[0] == ' '){
	string cmdCpy(cmdString);
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
	char* cstr = new char[cmdCpy.length()+1];
	strcpy(cstr, cmdCpy.c_str());
	cmdString = cstr;
     }
  
	char* tok;
	tok = strtok(cmdString, " ");
	char* args[64];
	
	pid_t pid;
	pid_t wpid;

	while (tok != NULL) {
		int status;
		
		args[0] = tok;
		args[1] = NULL;
		
		pid = fork();/* forks child process */
		
		if (pid == -1) {
		      perror("fork");
		} 
		else if (pid == 0){
	  
		      if(tok == an.c_str() && cmdStatus){ // && case
			  tok = strtok(cmdString, " "); //gets the next command
			  args[0] = tok;
			  if (execvp(args[0], args) < 0){ //? idk if this works
				  cmdStatus = false;
				  cout << "Didn't execute" << endl;
			  }
			  else {
				  cmdStatus = true;
				  tok = strtok(NULL, " "); //gets next command
			  }
		      }
		      else if (tok == o.c_str() && !cmdStatus){ // || case
			  tok = strtok(cmdString, " "); //gets the next command
			  args[0] = tok;
			  
			  if (execvp(args[0], args) < 0){ //? idk if this works
				  cmdStatus = false;
				  cout << "Didn't execute" << endl;
			  }
			  else {
				  cmdStatus = true;
				  tok = strtok(NULL, " ");
			  }
		      }
		      else if (execvp(args[0], args) < 0){ //? idk if this works //general case
			   cmdStatus = false;
			   cout << "Didn't execute" << endl;
		      }
		      else {
			  cmdStatus = true;
			  tok = strtok(NULL, " ");
		      }
		}
		else {//parent
		  do {
		    wpid = waitpid(pid, &status, WUNTRACED);
		  }
		  while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}
