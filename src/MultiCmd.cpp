#include "MultiCmd.h"

// Accessors and Mutators-------------
void MultiCmd::setCmd(char* str){
	cmdString = str;
	return;
}

char* MultiCmd::getCmd() const{
	return cmdString;
}

void MultiCmd::setCmdStatus(bool b) {
	cmdStatus = b;
}

bool MultiCmd::getCmdStatus() const{
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
  
  for(unsigned i = 0; tok != NULL; i++){ // Adds string tokens into vector of tokens
    cmds.push_back(tok);
    tok = strtok(NULL, " ");
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
  Base* dum = new SingleCmd(); // Creates a dummy SingleCmd to hold the cmdStatus of prev executed commands
  
  leftPtr = cmdQueue.front(); // Assigns first element of queue to left ptr
  cmdQueue.pop();
  midPtr = cmdQueue.front(); // Assigns second element of queue to mid ptr // should be connector
  cmdQueue.pop();
  rightPtr = cmdQueue.front(); // Assigns third element of queue to right ptr 
  cmdQueue.pop();
  
  midPtr->setLeftCmd(leftPtr); // sets left command of mid
  midPtr->setRightCmd(rightPtr); // sets right command of mid
  
  midPtr->execute(); 
  
  while (!cmdQueue.empty()){
    dum->setCmdStatus(midPtr->getCmdStatus()); // sets dummy's status to the last midpointers status
   
    midPtr = cmdQueue.front(); // sets new mid pointer
    cmdQueue.pop();
    rightPtr = cmdQueue.front(); // sets new right pointer
    cmdQueue.pop();
    
    midPtr->setLeftCmd(dum); // sets new mid left to dummy
    midPtr->setRightCmd(rightPtr); // set new mid right to new right
    
    if (midPtr == NULL || rightPtr == NULL){ // checks if the elemnt is null
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
