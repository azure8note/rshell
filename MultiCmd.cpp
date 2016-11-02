#include "MultiCmd.h"

void MultiCmd::setCmd(char* str){
	cmdString = str;
	return;
}

char* MultiCmd::getCmd() const{
	return cmdString;
}

void MultiCmd::setStatus(bool b) {
	cmdStatus = b;
}

bool MultiCmd::getStatus() const{
	return cmdStatus;
}

void MultiCmd::parse() {
  
  if(cmdString[0] == ' '){// removes space in front of ;
	string cmdCpy(cmdString);
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
	char* cstr = new char[cmdCpy.length()+1];
	strcpy(cstr, cmdCpy.c_str());
  }
  
  char* tok;
  
  tok = strtok(cstr, ' ');
  cmds.push_back(tok);
  
  for(unsigned i = 0; tok != NULL; i++){//changes string into vector of tokens
    tok = strtok(NULL, ' ');
    cmds.push_back(tok);
  }
}

void MultiCmd::makeQueue() {
  
  string an = "&&";
  string o = "||";
  
  Base* temp = 0;
  
  for(unsigned i = 0; i < cmds.size(); i++){
     if (cmds.at(i) == an.c_str()){
       temp = new And();
       cmdQueue.push(temp);
     }
     else if (cmds.at(i) == o.c_str()){
       temp = new Or();
       cmdQueue.push(temp);
     }
     else {
       temp = new SingleCmd(cmds.at(i));
       cmdQueue.push(temp);
     }
  }
}

void MultiCmd::execute() {
  
  this->parse();
  this->makeQueue();
  
  Base* leftPtr;
  Base* midPtr;
  Base* rightPtr;
  Base* dum = new SingleCmd();
  
  leftPtr = cmdQueue.front();
  cmdQueue.pop();
  midPtr = cmdQueue.front();
  cmdQueue.pop();
  rightPtr = cmdQueue.front();
  cmdQueue.pop();
  
  midPtr->setLeft(leftPtr);
  midPtr->setRight(rightPtr);
  
  midPtr->execute();
  
  while (!cmdQueue.empty()){
    dum->setStatus(midPtr->getStatus());
    midPtr = cmdQueue.front();
    cmdQueue.pop();
    rightPtr = cmdQueue.front();
    cmdQueue.pop();
    midPtr->execute();
  }
}
  
      
 /*
	char* tok;
	tok = strtok(cmdString, " ");
	char* args[64];
	
	pid_t pid;
	pid_t wpid;

	while (tok != NULL) {
		int status;
		
		args[0] = tok;
		args[1] = NULL;
		
		pid = fork();/* forks child process
		
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
	*/
