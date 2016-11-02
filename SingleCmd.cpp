#include "SingleCmd.h"

void SingleCmd::changeCmd(char* str){
	cmd = str;
	return;
}

char* SingleCmd::readCmd() {
	return cmd;
}

void SingleCmd::execute() {
  
  char* args[2];
  args[0] = cmd;
  args[1] = NULL;
  
  pid_t pid;
  
	if ((pid = fork()) < 0) { /*fork a child process*/
	    perror("fork");
	} else if(pid == 0){ //child processs
	  if (execvp(args[0], args) < 0){
		perror ("exec");
	  }
	}
	else {//parent
	  if (wait(0) == -1){
	    perror("wait");
	  }
	}
}
