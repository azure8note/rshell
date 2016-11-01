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

	char* cmd;
	cmd = strtok(cmdString, " ");
	char* args[2];
	
	
	pid_t pid;
	int status;
	
	while (cmd != NULL) {
		args[0] = cmd;
		args[1] = NULL;
		
		if (pid = fork() == -1) {/* forks child process */
		      perror("fork");
		}
		else if (pid == 0){
	  
		      if( *cmd == "&&" && cmdStatus){// && case
			  cmd = strtok(cmdString, " ");//gets the next command
			  args[0] = cmd;
			  if (execvp(cmd, args) < 0){//? idk if this works
				  cmdStatus = false;
				  cout << "Didn't execute" << endl;
			  }
			  else {
				  cmdStatus = true;
				  cmd = strtok(NULL, " ");//gets next command
			  }
		      }
		      else if ( *cmd == "||" && !cmdStatus){ // || case
			  cmd = strtok(cmdString, " ");//gets the next command
			  args[0] = cmd;
			  
			  if (execvp(cmd, args) < 0){//? idk if this works
				  cmdStatus = false;
				  cout << "Didn't execute" MM endl;
			  }
			  else {
				  cmdStatus = true;
				  cmd = strtok(NULL, " ");
			  }
		      }
		      else if (execvp(cmd, args) < 0){//? idk if this works //general case
			   cmdStatus = false;
			   cout << "Didn't execute" << endl;
		      }
		      else {
			  cmdStatus = true;
			  cmd = strtok(NULL, " ");
		      }
		}
		else {// parent
		    if (wait(0) == -1){
		      perror("wait");
		    }
		}
	}
}
