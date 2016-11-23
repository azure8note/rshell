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
    string cmdCpy(cmd);
    
    if (cmdCpy.at(0) == '[' && cmdCpy.find("]") == string::npos) { // Error: no closing bracket
		throw "INVALID INPUT: [ WITH NO CLOSING ]";
    }

    if (cmd[0] == ' '){ // If there is a space after the ';', this removes it.
	    
		while (cmdCpy.at(0) == ' '){ // Removes parentheses around single commands
	  		cmdCpy = cmdCpy.substr(1, cmdCpy.size()-1);
		}
	
		char* cstr = new char[cmdCpy.length()+1];
		strcpy(cstr, cmdCpy.c_str());
		cmd = cstr;
    }
    
    if (cmd[0] == '(') { // Check for parentheses
		while (cmdCpy.at(0) == '('){ // Removes parentheses around single commands
	  		cmdCpy = cmdCpy.substr(1, cmdCpy.size()-2);
		}	
	
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
    try { 
		this->parse(); // Further parses cmd into the actual command and any flags it has
    } catch (const char* err_msg) { // Catch INVALID INPUT error
		cerr << err_msg << endl; // Prints to console error message
		return; // Ends call to execute
    }

    string argsCpy(args[0]);
    struct stat sb;
    
    
    if (argsCpy == "cd") { //looks for cd command  
	
	}	
	
    try {    
	    if (argsCpy == "test" || argsCpy == "[") { // Looks for test command
    	    string firstTok(args[1]); 
	    
			if (firstTok.at(0) != '-') { // Checks if a flag is provided with the test command
	    		if (stat(args[1], &sb) == -1) { // Path given in index 1 when no flag is provided
        			perror("stat"); // Error check
	   		 	}	
	    	

	    		if (access(args[1], F_OK) == 0) { // Check if the file exists at given path
					cout << "(True)" << endl;
	    		} else {
					cout << "(False)" << endl;	
					setCmdStatus(false); // Set cmdStatus to false
	    		}
	    
	   	 		return;	
			}	  

			if (argsCpy == "test" && firstTok.at(0) == '-' && args[2] == NULL) {
	    		throw "INVALID INPUT: NO PATH PROVIDED";
			} else if (argsCpy == "[" && firstTok.at(0) == '-' && args[3] == NULL) {
	    		throw "INVALID INPUT: NO PATH PROVIDED";
        	}

			if (stat(args[2], &sb) == -1) { // Initialize stat with path given at index 2
            	perror("stat");
			}

			if (firstTok.at(1) == 'e') { // Check for -e flag
	    		if (access(args[2], F_OK) == 0) { // If the file exists, print (True)
					cout << "(True)" << endl;
	   			} else { // File does not exist
					cout << "(False)" << endl; 
					setCmdStatus(false); // Set cmdStatus to false
	    		}	
			} else if (firstTok.at(1) == 'f') { // Check for -f flag
	    		if (S_ISREG (sb.st_mode)) { // Check if it is a regular file
					cout << "(True)" << endl;
	    		} else {
					cout << "(False)" << endl;
					setCmdStatus(false);
	    		}
			} else { // -d flag
	    		if (S_ISDIR (sb.st_mode)) { // Check if it is a directory
					cout << "(True)" << endl;
	    		} else {
					cout << "(False)" << endl;
					setCmdStatus(false);
	    		}
			}   
        	return;
    	} // Closes fisrt if statement in try block
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
	   	 perror("fork");// Didn't fork properly
	} 
	else if(pid == 0){ // Child processs
	  	if (execvp(args[0], args) < 0){// Calls execute
			setCmdStatus(false);// In case it fails changes the status (for multi comand
			perror ("exec"); // Error check
	  	}	
	}
	else { // Parent
		pid_t wpid; // Waits for child to finish
	  	
		wpid = waitpid(pid, &status, WUNTRACED);
		
		if (status > 0){
			setCmdStatus(false);
		}
		
		while (wpid <= -1){
		    perror("wait");
		    wpid = waitpid(pid, &status, WUNTRACED);
		} 
    }
}
