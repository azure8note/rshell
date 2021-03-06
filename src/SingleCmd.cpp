#include "SingleCmd.h"

using std::cerr;
using std::endl;

/* Accessors and Mutators */
char* SingleCmd::getCmd() const{
    return cmd;
}

bool SingleCmd::getCmdStatus() const{
    return cmdStatus;
}

void SingleCmd::setCmd(char* str){
	cmd = str;
	return;
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

/* executeCd helper function - parses path and handles multiple .. and . */ 
string SingleCmd::parseCd(string cwd) {	
	string firstTok(args[1]);

	if (firstTok == "." || firstTok == "./") {
		// Do not modify cwd
		return cwd;
	} else if (firstTok == ".." || firstTok == "../") {
		unsigned int index = cwd.size() - 1; // Index of last element in cwd
		while (cwd.at(index) != '/') { // Find the end of path for the next directory up
			--index; // Index will decrement until it finds / which separates directories
		}
		
		cwd = cwd.substr(0, index); // Create substring of cwd path up to second to last directory
		return cwd;
	} else if (firstTok.find("/") == string::npos) {
		cwd += "/";
		cwd += firstTok; // Concatenate / and new directory to prev. working directory
		return cwd;
	}

	char* tokptr = strtok(args[1], "/"); // Set tokptr to beginning of path
	
	while (tokptr != NULL) {
		if (strcmp(tokptr,".") == 0) { // Stay in current directory
			 // Do not modify cwd
		} else if (strcmp(tokptr,"..") == 0) { // Go back one directory	
			unsigned int index = cwd.size() - 1; // Index of last element in cwd
			while (cwd.at(index) != '/') { // Find the end of path for the next directory up
				--index; // Index will decrement until it finds / which separates directories
			}

			cwd = cwd.substr(0, index); // Create substring of cwd path up to second to last directory
		} else { // Specified directory
			string dir(tokptr);
			cwd += "/";
			cwd += dir; // Concatenate / and new directory to prev. working directory
		}
		tokptr = strtok(NULL, "/"); // Continue searching for tokens from last successful return
	}

	return cwd;
}

/* execute helper function - handles execution of cd commands */
void SingleCmd::executeCd() {
	
	string cwd(getenv("PWD")); // Store current working directory as string
        
	if (args[1] == NULL) { // No argument supplied, return to home directory
		if (chdir(getenv("HOME")) == -1) { // Change pwd to home, chdir returns -1 upon failure
        		perror("ERROR: COULD NOT REACH HOME DIRECTORY");
        		setCmdStatus(false);
        	}
		if (setenv("OLDPWD", getenv("PWD"), 1) == -1) { // Update OLDPWD to PWD, setenv returns -1 if it fails
        		perror("ERROR: COULD NOT UPDATE OLDPWD");
		}
        	if (setenv("PWD", getenv("HOME"), 1) == -1) { // Update PWD to HOME
        		perror("ERROR: COULD NOT SET PWD");            
        	}
	} else if (*(args[1]) == '-') { // Return to previous directory
        	if (chdir(getenv("OLDPWD")) == -1) {
			perror("ERROR: COULD NOT ACCESS OLDPWD");
			setCmdStatus(false);
		}
		if (setenv("PWD", getenv("OLDPWD"), 1) == -1) { // Update PWD to OLDPWD
			perror("ERROR: COULD NOT SET PWD");
		}             
		if (setenv("OLDPWD", cwd.c_str(), 1) == -1) { // Update OLDPWD to earlier PWD
			perror("ERROR: COULD NOT UPDATE OLDPWD");
		}             
	} else { // Change working directory to specified path
		if (chdir(args[1]) == -1) {
			perror("ERROR: COULD NOT REACH DIRECTORY");
			setCmdStatus(false);
		}
		if (setenv("OLDPWD", cwd.c_str(), 1) == -1) { // Update OLDPWD to earlier PWD
			perror("ERROR: COULD NOT UPDATE OLDPWD");
		}

		cwd = parseCd(cwd); // Parse the path for multiple .. and .
	
		if (setenv("PWD", cwd.c_str(), 1) == -1) { // Update PWD to provided path
			perror("ERROR: COULD NOT SET PWD TO NEW DIRECTORY");
		}
	}
	return;
}

/* execute helper function - handles execution of test commands */
void SingleCmd::executeTest() {
	struct stat sb;
	string argsCpy(args[0]);
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
}

/* Executes exit and commands located in bin */
void SingleCmd::execute() {
    try { 
		this->parse(); // Parse cmd into the actual command and any flags it has
    } catch (const char* err_msg) { // Catch INVALID INPUT error
		cerr << err_msg << endl; // Print to console error message
		return; // End call to execute
    }
 
    string argsCpy(args[0]);
  
    if (argsCpy == "cd") { // Looks for cd command  
    	executeCd();
		return;
	}

    try {	 
		if (argsCpy == "test" || argsCpy == "[") { // Looks for test command
			executeTest();
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
