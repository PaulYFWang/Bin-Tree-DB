#include "DBentry.h"
#include <iostream>
using namespace std;

DBentry::DBentry(){
    name = "";
    IPaddress = 0;
    active = false;
}

DBentry::~DBentry(){
    
}
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

void DBentry::setName(string _name){
    name = _name;
}

   // sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
}

// returns the name.
string DBentry::getName() const{
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const{
    return active;
}
void DBentry::print(){
    if (active)
    cout << name << " : "<<IPaddress << " : active" << endl;
    else
         cout << name << " : "<<IPaddress << " : inactive" << endl;
}
// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
//ostream& DBentry::operator<< (ostream& out, const DBentry& rhs){
//    return
//}