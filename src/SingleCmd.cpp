#include "SingleCmd.h"

using std::cerr;
using std::endl;

//setters and getters --------------
void SingleCmd::setCmd(char* str){
	cmd = str;
	return;
}

char* SingleCmd::getCmd() const{
    return cmd;
}

bool SingleCmd::getCmdStatus() const{
    return cmdStatus;
}

void SingleCmd::setCmdStatus(bool b){
    cmdStatus = b;
}
//----------------------------------

void SingleCmd::parse() { // Seperates the command from its flag into two seperate tokens  
    char* tok;

    if (cmd[0] == ' '){ // If there is a space after the ';', this removes it.
	string cmdCpy(cmd);
	cmdCpy = cmdCpy.substr(1, cmdCpy.length() - 1);
	char* cstr = new char[cmdCpy.length()+1];
	strcpy(cstr, cmdCpy.c_str());
	cmd = cstr;
    }
  
    tok = strtok(cmd, " "); // First seperation
    args[0] = tok;

    for (unsigned i = 1; tok != NULL ; i++){ // Assigns the tokens into args
	tok = strtok(NULL, " ");
	args[i] = tok;
    }
}

void SingleCmd::execute() {
    this->parse(); // Further parses cmd into the actual command and any flags it has

    string argsCpy(args[0]);
    struct stat sb;
    
    try {
        if (argsCpy == "test" || argsCpy == "[") {
	    if (argsCpy == "[" && (*(args[2]) != ']' || *(args[3]) != ']')) {
	         throw "IVALID INPUT: [ WITH NO CLOSING ]";
	    }
	
            char firstTok[] = {*(args[1])};
	
            if (firstTok[0] != '-') {
	         if (access(firstTok, F_OK) == 0) {
		    cout << "(True)\n";
	         } else {
		    cout << "(False)\n";
	         }	
	    } else if (firstTok[1] == 'e') {
	         if (access(firstTok, F_OK) == 0) {
		    cout << "(True)\n";
	         } else {
		    cout << "(False)\n";
	         }	
	    } else if (firstTok[1] == 'f') {
	        if (S_ISREG (sb.st_mode)) {
		    cout << "(True)\n";
	        } else {
		    cout << "(False)\n";
	        }
	    } else {
	        if (S_ISDIR (sb.st_mode)) {
		    cout << "(True)\n";
	        } else {
		    cout << "(False)\n";
	        }
	    }   
            return;
	}	
    } catch (const char* err_msg) {
	cerr << err_msg << endl;
	return;
    }
 
    string lowExit = "exit";
    string capExit = "EXIT";
 
    if (argsCpy == lowExit || argsCpy == capExit) { // Checks for command exit
    	exit(0);
    }  

    pid_t pid; // For the forking
    int status; // For the waiting
  
    pid = fork(); // Fork from child process
  
    if (pid < 0) { // Fork a child process
   	perror("fork"); // Did not fork properly
    } 
    else if(pid == 0){ // Child processs
	if (execvp(args[0], args) < 0){ // Calls execute
	    setCmdStatus(false); // If it fails, changes cmdStatus to false (used in MultiCmd)
	    perror ("exec"); // Error checks
	}	
    } else { // Parent
  	pid_t wpid; // Waits for child to finish
	wpid = waitpid(pid, &status, WUNTRACED);
	  	
	while (wpid <= -1){
	    perror("wait");
	    wpid = waitpid(pid, &status, WUNTRACED);
	} 
    }
}
