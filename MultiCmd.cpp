#include "MultiCmd.h"
// getters and setters------------
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

void MultiCmd::parse() { // splits up the comand string into string tokens
  string cmdCpy(cmdString);
  char* cstr = new char[cmdCpy.length() + 1];
 
  if(cmdString[0] == ' '){// removes space in front of ;
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
  }
  
  strcpy(cstr, cmdCpy.c_str());
  char* tok;
  
  tok = strtok(cstr, " ");
  cmds.push_back(tok);
  
  for(unsigned i = 0; tok != NULL; i++){//changes string into vector of tokens
    tok = strtok(NULL, " ");
    cmds.push_back(tok);
  }
}

void MultiCmd::makeQueue() {
  
  string an = "&&";
  string o = "||";
  
  Base* temp = 0;
  
  for(unsigned i = 0; i < cmds.size(); i++){//loops through all commands turing them into differnet objects
     if (cmds.at(i) == an.c_str()){// checks to see if the cmd is a && connector
       temp = new And(); // creats and && object and pushes it into the queue so we know so it keesp the order
       cmdQueue.push(temp);
     }
     else if (cmds.at(i) == o.c_str()){ // creates and || object and and is pushed into queue
       temp = new Or();
       cmdQueue.push(temp);
     }
     else {
       temp = new SingleCmd(cmds.at(i)); // neither && or || so it makes a single command and pushes it into queue
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
