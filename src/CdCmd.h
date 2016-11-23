#ifndef CDCMD_H
#define CDCMD_H

#include "Base.h" // superclass
#include <stdlib.h> // getenv, setenv
#include <string>
#include <unistd.h> // chdir

class CdCmd : public Base {	
	public:
		/* Constructors */
		CdCmd() : Base() {}
		CdCmd(char* path) : Base() {}

		/* Accessors and Mutators */
		string getPWD() const;
		string getOLDPWD() const;
		void setPWD(string path);
		void setOLDPWD(string path);

		void execute();
}

#endif
