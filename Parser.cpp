#include <cstdlib>
#include "Parser.h"
using namespace std;
Parser::~Parser(){
    
}
Parser::Parser(stringstream &stream_){
    stream = stream_.str();
    extractCommand();
    
}
Parser::Parser(){
    stream = "";
}
string Parser::getCommand(){
    return command;
    
}
void Parser::extractCommand(){
    stringstream s (stream);
    //cout <<stream << " from parse pre command r" <<endl;
    s >> command;
    stream = stream.substr(stream.find_first_of(" \t")+1);
    //cout <<stream << " from parser after command" <<endl;

}
void Parser::newCommandStream(stringstream &stream_){
    stream = stream_.str();
    extractCommand();
}


void Parser::insert(){
    stringstream s (stream);
    s >> name;
    s >> resistance;

    
}

void Parser::activeInsert(){
    n.findOrCreateNode(nodeID1);
    n.findOrCreateNode(nodeID2);
    if(!n.addResistor(name,resistance,nodeID1,nodeID2))
        cout<<"Error: resistor "<< name <<" already exists"<< endl;
    else{
        cout << "Inserted: resistor "<<name<< " "<< fixed << setprecision(2)<<resistance<< " Ohms "<<nodeID1 <<" -> " << nodeID2 << endl;
    }
}


void Parser::modifyR(){
     stringstream s (stream);
     s >> name;
     s >> resistance;
}
void Parser::activeModifyR(){
    int node1, node2;
    double oldRes;
    if(n.findResistor(name) == NULL)
        cout <<"Error: resistor "<<name<<" not found"<<endl;
    else{
        node1 = n.findResistor(name)->endpointNodeIDs[0];
        node2 = n.findResistor(name)->endpointNodeIDs[1];
        oldRes = n.findResistor(name)->resistance;
        n.findNode(node1)->findResistor(name)->setResistance(resistance);
        n.findNode(node2)->findResistor(name)->setResistance(resistance);
        cout <<"Modified: resistor " << name<< " from "<< fixed << setprecision(2) << oldRes << " Ohms to "<< fixed << setprecision(2)<< resistance << " Ohms" <<endl;
    }
}
void Parser::printR(){
    stringstream s (stream);
    s >> name;
    
}
void Parser::activePrintR(){
    if(n.findResistor(name) == NULL)
        cout <<"Error: resistor "<<name<<" not found"<<endl;
    else{
        cout <<"Print:\n";
        n.findResistor(name)->print();
    }
}
void Parser::printNode(){
    stringstream s (stream);
    stringstream s2(stream);
    s >> nodeID;

    if (s.fail()){
;
	s.clear();
        s >> all;

        nodeID = -1;
        streamFail = true;
    }
    else
        streamFail = false;
}
void Parser::activePrintNode(){
    if(streamFail){
        cout <<"Print:\n";
        n.printAll();
    }
    else{
        if (!n.printNode(nodeID))
            cout <<"Error: node "<< nodeID << " not found"<<endl;
    }
}
void Parser::deleteR(){
    stringstream s (stream);
    s >> all;
    
}
void Parser::activeDeleteR(){
    int id1, id2;
    if (all == "all"){
        n.deleteAllResistors();
        cout <<"Deleted: all resistors" << endl;
    }
    else{
        if(n.findResistor(all) == NULL)
            cout <<"Error: resistor "<<all<<" not found"<<endl;
        else{
            id1 = n.findResistor(all)->endpointNodeIDs[0];
            id2 = n.findResistor(all)->endpointNodeIDs[1];
            n.findNode(id1)->r.deleteResistor(all);
            n.findNode(id2)->r.deleteResistor(all);
            cout <<"Deleted: resistor "<<all<<endl;
        }
    }
}
void Parser::setV(){
    stringstream s(stream);
    s >> nodeID;
    s >> voltage;
}
void Parser::activeSetV(){
    if(!n.setVoltage(nodeID,voltage))
        cout<<"Error: node "<< nodeID << " not found"<<endl;
    else
        cout <<"Set: node "<<nodeID<< " to " << fixed << setprecision(2)<< voltage<<" Volts"<<endl;
}
void Parser::unsetV(){
    stringstream s(stream);
    s >> nodeID;
}


void Parser::activeUnsetV(){
    if(!n.unsetVoltage(nodeID))
        cout << "Error: node "<< nodeID << " not found"<<endl;
    else
        cout <<"Unset: the solver will determine the voltage of the node " << nodeID<<endl;
}
void Parser::solve(){
    if(n.solvable()){
       
        n.initSolve();
        while(n.solve()>0.0001){
        }
        
        cout<<"Solve:\n";
        n.printNodeAllV();
    }
    else {
        cout <<"Error: no nodes have their voltage set" << endl;
    }
    
}
    
