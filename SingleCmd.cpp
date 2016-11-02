#include "SingleCmd.h"

void SingleCmd::changeCmd(char* str){
	cmd = str;
	return;
}

char* SingleCmd::readCmd() {
	return cmd;
}

void SingleCmd::execute() {
  
  if(cmd[0] == ' '){
     string cmdCpy(cmd);
     cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
     char* cstr = new char[cmdCpy.length()+1];
     strcpy(cstr, cmdCpy.c_str());
     cmd = cstr;
  }
  
  string lowE = "exit";
  string capE = "EXIT";
  
  char* tok;
  
  char* args[64];
  
  tok = strtok(cmd, " ");
  
  for (unsigned i = 0; tok != NULL ; i++){
    tok = strtok(NULL, " ");
    args[i] = tok;
  }
  
  if (tok == lowE.c_str() || tok == capE.c_str()){
    exit(0);
  }

  pid_t pid;
  pid_t wpid;
  int status;
  
	pid = fork();
  
	if (pid < 0) { /*fork a child process*/
	    perror("fork");
	} 
	else if(pid == 0){ //child processs
	  if (execvp(args[0], args) < 0){
		perror ("exec");
	  }
	}
	else {//parent
	  do {
	    wpid = waitpid(pid, &status, WUNTRACED);
	  }
	  while(!WIFEXITED(status) && !WIFSIGNALED(status));}
}
