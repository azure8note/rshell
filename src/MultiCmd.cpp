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

//----------------------------------------

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
//---------------------   
    int openCounter = 0;
    int closeCounter = 0;
    
    //maybe only need to check the first char since that how it statrts
    if (cmdCpy.at(0) == '('){
       unsigned i = 0;
       openCounter++; // found a parenthesis 
       while (openCounter > closeCounter){ //looks for the last closing parethesis for this part
          i++;
          if (cmdCpy.at(i) == '('){
	     openCounter++;
	  }
	  if (cmdCpy.at(i) == ')'){
             closeCounter++;
	  }
      }
      //index is now pointing to the location of the last parenthesis
      index = i+1;
    }
//------------------------	      
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
//for parenthsesis
    openCounter = 0;
    closeCounter = 0;
    if (cmdCpy.at(0) == '('){
      unsigned i = 0;
      openCounter++; // found a parenthesis 
      while (openCounter > closeCounter){ //looks for the last closing parethesis for this part
         i++;
	 if (cmdCpy.at(i) == '('){
	     openCounter++;
	 }
	 if (cmdCpy.at(i) == ')'){
	     closeCounter++;
	 }
       }
       index = i+1; //index is now pointing to the location of the last parenthesis
    }
//-------------------------
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
      //checks if the the string has parentheses
      bool has_Par = false;
      for (unsigned j = 0;(cmds.at(i))[j] != '\0'; j++) {//since we removed first '(' we have to loop through it
	  if ((cmds.at(i))[j] == '(' || (cmds.at(i))[j] == ')' ){
	     has_Par = true;
	     break;
	  }
      }	
      
      if (has_Par){ // If it has parentheses
	string cmdCpy(cmds.at(i));
	string tempStr;
	char* cstr = new char[cmdCpy.length() + 1];
	
	tempStr = cmdCpy.substr(1, cmdCpy.length()-2); // Removes first and last parentheses
	strcpy(cstr, tempStr.c_str());
	
	temp = new MultiCmd(cstr);
	cmdQueue.push(temp);
      }
      
      else if ((cmds.at(i))[0] == '&'){ // Checks if cmd is an && connector
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
     cerr << "INVALID INPUT: TWO CONNONECTORS IN A ROW\n";
     return;
  }
  catch (char MISSING_SECOND_ARGUMENT) {
    cerr << "INVALID INPUT: CONNECTORS NEED TWO ARGUMENTS\n";
    return;
  }
  this->makeQueue();
  
  Base* leftPtr; 
  Base* midPtr; // Takes leftPtr and rightPtr as its left & right children
  Base* rightPtr;
  Base* dum = new SingleCmd(); // Creates a dummy SingleCmd to hold the cmdStatus of prev executed commands
  
  leftPtr = cmdQueue.front(); // Assigns first element of queue to leftPtr
  cmdQueue.pop();
  midPtr = cmdQueue.front(); // Assigns second element (should be a connector) of queue to midPtr 
  cmdQueue.pop();
  rightPtr = cmdQueue.front(); // Assigns third element of queue to rightPtr
  cmdQueue.pop();
  
  midPtr->setLeftCmd(leftPtr); // Sets left command of mid
  midPtr->setRightCmd(rightPtr); // Sets right command of mid
  
  midPtr->execute(); 
  
  while (!cmdQueue.empty()){
    dum->setCmdStatus(midPtr->getCmdStatus()); // Sets the SingleCmd dummy's status to the last midpointers status
   
    midPtr = cmdQueue.front(); // Sets new mid pointer
    cmdQueue.pop();
    rightPtr = cmdQueue.front(); // Sets new right pointer
    cmdQueue.pop();
    
    midPtr->setLeftCmd(dum); // Sets new mid left to dummy
    midPtr->setRightCmd(rightPtr); // Set new mid right to new right
    
    if (midPtr == NULL || rightPtr == NULL){ // checks if the elemnt is null
      return;
    }
    midPtr->execute();
    this->cmdStatus = midPtr->getRightCmd()->getCmdStatus();
  }
}

