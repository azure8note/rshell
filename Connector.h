#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"

class Connector : public Base {
  
  protected:
    
    virtual Base* getLeftCmd() const {};
    virtual Base* getRightCmd() const {};
    virtual bool getCmdStatus() const {};
    virtual void setLeftCmd(Base*) {};
    virtual void setRightCmd(Base*) {};
  
  public:
    Connector() {};
    
};

#endif