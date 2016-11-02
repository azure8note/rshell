#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"

class Connector : Public Base {
  
  protected:
    
  virtual Base* getLeftCmd() const = 0;
  virtual Base* getRightCmd() const = 0;
  virtual bool getCmdStatus() const = 0;
  virtual void setLeftCmd(Base*) = 0;
  virtual void setRightCmd(Base*) = 0;
  
  public:
    Connector() {};
    
};

#endif