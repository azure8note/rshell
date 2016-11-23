#include "cdCmd.h"

//-------GETTER AND SETTERS ---------
string cdCmd::getPWD() const {
   return pwd;
}

void cdCmd::setPWD(string path) {
   pwd = s;
}

string cdCmd::getOLDPWD() const {
   return oldPwd;
}

void cdCmd::setOLDPWD(string path) {
  oldPwd = s;
}
//--------------------------------

void cdCmd::execute() {
  
}

