#include "MultiCmd.h"

// Accessors and Mutators-------------
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

//------------------------------------

void MultiCmd::parse() { // Splits the command string into string tokens
  string cmdCpy(cmdString);
  char* cstr = new char[cmdCpy.length() + 1];
 
  if(cmdString[0] == ' ') { // Removes space behind ; 
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
  }
  
  strcpy(cstr, cmdCpy.c_str()); // Creates mutable c-string copy of cmdCpy
  char* tok;
  
  tok = strtok(cstr, " ");
  cmds.push_back(tok);
  
  for(unsigned i = 0; tok != NULL; i++){ // Adds string tokens into vector of tokens
    tok = strtok(NULL, " ");
    cmds.push_back(tok);
  }
}

void MultiCmd::makeQueue() {
  
  Base* temp = 0;
  
  /* Iterates the vector of commands, instantiating
     the correct corresponding object */
  for(unsigned i = 0; i < cmds.size(); i++){
     if ((cmds.at(i))[0] == '&'){ // Checks if cmd is an && connector
       temp = new And(); // Creates And object and pushes it into queue
       cmdQueue.push(temp);
     }
     else if ((cmds.at(i))[0] == '|'){ // Creates Or object and pushes it into queue
       temp = new Or();
       cmdQueue.push(temp);
     }
     else { // Not && or || connector
       temp = new SingleCmd(cmds.at(i)); // Creates SingleCmd and pushes it into queue
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
  SingleCmd* dum = new SingleCmd();
  
  leftPtr = cmdQueue.front();
  cmdQueue.pop();
  midPtr = cmdQueue.front();
  cmdQueue.pop();
  rightPtr = cmdQueue.front();
  cmdQueue.pop();
  
  midPtr->setLeftCmd(leftPtr);
  midPtr->setRightCmd(rightPtr);
  
  midPtr->execute();
  
  while (!cmdQueue.empty()){
    dum->setStatus(midPtr->getCmdStatus());
    midPtr = cmdQueue.front();
    cmdQueue.pop();
    rightPtr = cmdQueue.front();
    cmdQueue.pop();
    if (midPtr == NULL || rightPtr == NULL){
      return;
    }
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
		
		pid = fork(); forks child process
		
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
