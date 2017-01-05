/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on November 24, 2016, 2:31 PM
 */

#include <cstdlib>
#include "DBentry.h"
#include  "TreeDB.h"
#include "TreeNode.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
     string line;//Declaring variables
     string name, status, cmd;
     bool stat;
     TreeDB tree;
     int ip;
     cout << "> ";
    getline (cin, line);
  ;
   //Instancing Parser
    
	//Runs until it eofs
    while (!cin.eof()){
        stringstream stream(line);
        stream >> cmd;
        if(cmd == "insert"){
            stream >> name;
            stream >> ip;
            stream >> status;
            //cout << name << ip << status;
            if(status == "active")
                stat = true;
            else
                stat = false;
            DBentry* entry = new DBentry(name, ip, stat);
            if(tree.insert(entry))
                cout << "Success" << endl;
            else
                cout <<"Error: entry already exists"<<endl;
        }
        else if (cmd == "find"){
            stream >> name;
            if(tree.find(name) != NULL)
                tree.find(name)->print();
            else
                cout << "Error: entry does not exist"<<endl;
        }
        else if (cmd == "remove"){
            stream >> name;
            if(tree.remove(name))
                cout <<"Success" << endl;
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if (cmd== "printall"){
            tree.printall();
        }
        else if (cmd == "printprobes"){
            stream >> name;
            tree.printProbes(name);
        }
        else if (cmd == "removeall"){
           
            tree.clear();
            cout <<"Success"<<endl;
        }
        else if (cmd == "countactive"){
            cout <<tree.countActive() << endl;
        } 
        else if (cmd == "updatestatus"){
            stream >> name;
            stream >> status;
            if(status == "active")
                stat = true;
            else
                stat = false;
            if(tree.find(name)!= NULL){
                cout <<"Success" << endl;
                tree.find(name)->setActive(stat);
            }
            else 
                cout << "Error: entry does not exist" << endl;
            
        }
            stream.clear();
            stream.ignore(1000, '\n');
            cout<< "> ";
            getline (cin, line);

        
    }
cout <<"> " <<endl;
   
    return 0;
}

