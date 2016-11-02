#ifndef BASE_H
#define BASE_H

class Base {
public:
	//Constructor
	Base() {};
	//Pure virtual function
	virtual void execute() = 0;
    virtual Base* getLeftCmd() const {};
    virtual Base* getRightCmd() const {};
    virtual bool getCmdStatus() const {};
    virtual void setLeftCmd(Base*) {};
    virtual void setRightCmd(Base*) {};

};

#endif
