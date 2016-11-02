#ifndef BASE_H
#define BASE_H

#include <stddef.h>

class Base {
public:
	//Constructor
	Base() {};
	//Pure virtual function
	virtual void execute() = 0;
    virtual Base* getLeftCmd() const { return NULL;};
    virtual Base* getRightCmd() const { return NULL;};
    virtual bool getCmdStatus() const { return false;};
    virtual void setLeftCmd(Base*) {};
    virtual void setRightCmd(Base*) {};
    virtual char* getCmd() const {return NULL;};
};

#endif
