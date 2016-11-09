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

//exceptions
  int DOUBLE_CONNECTOR_EXCEPTION = 10;
  char MISSING_SECOND_ARGUMENT = 'z';

  string cmdCpy(cmdString);
  char* cstr = new char[cmdCpy.length() + 1];
 
  while(cmdString[0] == ' ') { // Removes space behind ; 
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
  }
  
  //strcpy(cstr, cmdCpy.c_str()); // Creates mutable c-string copy of cmdCpy
  
  string andDelimiter = "&&";
  string orDelimiter = "||";
  
  unsigned index = 0;
  string temp;
  string connector;
  
    if (cmdCpy.find(andDelimiter) < cmdCpy.find(orDelimiter)) {//str::npos returns largest unsigned value
      index = cmdCpy.find(andDelimiter);
    } else {
      index = cmdCpy.find(orDelimiter);
    }
    
    temp = cmdCpy.substr(0, index);
    cmdCpy = cmdCpy.substr(index, cmdCpy.size()-index);
    strcpy(cstr, temp.c_str());
    cmds.push_back(cstr);
 
  
  while (cmdCpy.find(andDelimiter) != string::npos || cmdCpy.find(orDelimiter) != string::npos){
    char* cstr2 = new char[2];
    
    while (cmdCpy[0] == ' ') { // Removes space behind ; 
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
    }
    //pushes connector into the cmds vector
    connector = cmdCpy.substr(0, 2);
    cmdCpy = cmdCpy.substr(2, cmdCpy.size()-2);
    strcpy(cstr2, connector.c_str());
    cmds.push_back(cstr2);
    
    while (cmdCpy[0] == ' ') { // Removes space behind ; 
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
    }
   
try{    //checks to see if double connector or no second argument
    if (cmdCpy.find(andDelimiter) < cmdCpy.find(orDelimiter)) {//str::npos returns largest unsigned value
      index = cmdCpy.find(andDelimiter);
      if (index == 0){
	throw  DOUBLE_CONNECTOR_EXCEPTION;
      }
    } 
    else if(cmdCpy.find(andDelimiter) > cmdCpy.find(orDelimiter)) {
      index = cmdCpy.find(orDelimiter);
      if (index == 0){
	throw DOUBLE_CONNECTOR_EXCEPTION;
      }
    }
    else {
      index = cmdCpy.size();
      if (index == 0){
	throw MISSING_SECOND_ARGUMENT;
      }
    }
}catch (int DOUBLE_CONNECTOR_EXCEPTION) {//throws to be caught in execute
  throw DOUBLE_CONNECTOR_EXCEPTION;
  break;
}
catch (char MISSING_SECOND_ARGUMENT) {//throws to be caught in exeute
  throw MISSING_SECOND_ARGUMENT;
  break;
}

   
    temp = cmdCpy.substr(0, index);
    char* cstr3 = new char[temp.size()];
    cmdCpy = cmdCpy.substr(index, cmdCpy.size()-index);
    strcpy(cstr3, temp.c_str());
    cmds.push_back(cstr3);
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
try{  
  this->parse();
} catch (int DOUBLE_CONNECTOR_EXCEPTION){
     cout << "INVALID INPUT: TWO CONNONECTORS IN A ROW\n";
     return;
  }
  catch (char MISSING_SECOND_ARGUMENT) {
    cout << "INVALID INPUT: CONNECTORS NEED TWO ARGUMENTS\n";
    return;
  }
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
  