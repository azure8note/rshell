#ifndef OR_H
#define OR_H

#include "Connector.h"
#include <stddef.h>

class Or : public Connector {
	private:
		Base* leftCmd;
		Base* rightCmd;
		bool cmdStatus;

	public:
		// Constructor
		Or() : Connector(), leftCmd(NULL), rightCmd(NULL), cmdStatus(false) {};

		// Accessors for left, right command ptrs and cmdStatus
		Base* getLeftCmd() const;
		Base* getRightCmd() const;
		bool getCmdStatus() const;

		// Mutators for leftCmd, rightCmd, and cmdStatus 
		void setLeftCmd(Base* leftCmd);
		void setRightCmd(Base* rightCmd);
		void setCmdStatus(bool stat);

		// Calls execute 
		void execute();
};

#endif
