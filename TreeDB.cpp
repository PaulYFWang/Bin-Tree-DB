#include"TreeNode.h"
#include "DBentry.h"
#include "TreeDB.h"
#include <iostream>
using namespace std;
 TreeDB::TreeDB(){
     root = NULL;
     probesCount = 0;
 }

// the destructor, deletes all the entries in the database.
 TreeDB::~TreeDB(){
     
 }

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool  TreeDB::insert(DBentry* newEntry){
    if(root == NULL)
            root = new TreeNode(newEntry);
    else if (find(newEntry->getName()) != NULL)
        return false;
    else{
        
        //cout << "KAPPA";
            TreeNode* entry = new TreeNode(newEntry);
            insertRecursive(entry, root);
        
        
    }
    return true;
}
void TreeDB::insertRecursive(TreeNode* entry, TreeNode* curNode){
    //insertion lies in the right
    if(curNode->getEntry()->getName() < entry->getEntry()->getName()){
        if(curNode->getRight() == NULL){
            curNode->setRight(entry);
            //cout << "RIGHT" <<endl;
        }
        else 
            insertRecursive (entry, curNode->getRight());
            
        
    }
    //insertion is to the left
    else {
        if(curNode->getLeft()==NULL){
             curNode->setLeft(entry);
             //cout << "LEFT" <<endl;
        }
        else 
            insertRecursive(entry, curNode->getLeft());
        
    }
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry*  TreeDB::find(string name){
    probesCount = 0;
    if(root == NULL)
        return NULL;
    else
    return findRecursive(name, root);
}
DBentry* TreeDB::findRecursive(string name, TreeNode* curNode){
    probesCount += 1;
    if(curNode->getEntry()->getName() == name)
        return curNode->getEntry();
    else if((curNode->getEntry()->getName() < name && curNode->getRight() == NULL)||(curNode->getEntry()->getName() > name && curNode->getLeft() == NULL))
        return NULL;
    else if (curNode == NULL)
        return NULL;
    else{
        if(curNode->getEntry()->getName() < name)
           return findRecursive(name, curNode->getRight());
        else
            return findRecursive(name,curNode->getLeft());
    }
} 
TreeNode* TreeDB::findRecursiveNode(string name, TreeNode* curNode){
    
    if(curNode->getEntry()->getName() == name)
        return curNode;
    else if((curNode->getEntry()->getName() < name && curNode->getRight() == NULL)||(curNode->getEntry()->getName() > name && curNode->getLeft() == NULL))
        return NULL;
    else if (curNode == NULL)
        return NULL;
    else{
        if(curNode->getEntry()->getName() < name)
           return findRecursiveNode(name, curNode->getRight());
        else
            return findRecursiveNode(name,curNode->getLeft());
    }
} 

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).

int TreeDB::count(TreeNode* curNode){
    int count = 1;
    
    if(curNode->getLeft() != NULL)
        count += countActiveRecursive(curNode->getLeft());
    if (curNode->getRight() != NULL)
        count += countActiveRecursive(curNode->getRight());
    return count;
}

int TreeDB::countActiveRecursive(TreeNode* curNode){
    int count = 0;
    if(curNode->getEntry()->getActive())
        count = 1;
    if(curNode->getLeft() != NULL)
        count += countActiveRecursive(curNode->getLeft());
    if (curNode->getRight() != NULL)
        count += countActiveRecursive(curNode->getRight());
    return count;
}
int TreeDB::countActive(){
    if(root != NULL)
    return countActiveRecursive(root);
    else 
        return 0;
}
// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool  TreeDB::remove(string name){
    if(find(name) != NULL && root != NULL){
        TreeNode* beforeRemove;
        TreeNode* removePoint;
        TreeNode* rightmostLeft;
        TreeNode* beforeRightmostLeft;
        TreeNode* temp1;
        TreeNode* temp2;
        bool rightSide = true;
        if(root->getEntry()->getName()==name){
            
            
           if( root->getLeft()!= NULL){
               
               
               if (root->getLeft()->getRight()!=NULL){
                   temp1 = root->getRight();
                   temp2 = root->getLeft();
                   rightmostLeft = findBeforeRightmostLeft(root->getLeft())->getRight();
                   findBeforeRightmostLeft(root->getLeft())->getRight();
                   root->deleteNode();
                   delete root;
                   root = rightmostLeft;
                   rightmostLeft->setLeft(temp2);
                   rightmostLeft->setRight(temp1);
               }
                   
               else{
                   temp1 = root->getRight();
                   temp2 = root->getLeft();
                   root->deleteNode();
                   delete root;
                   root = temp2;
                   root->setRight(temp1);
               }
                    
           }
           else{
               temp1 = root->getRight();
               root->deleteNode();
               delete root;
               root =temp1;
           }  
           
        }
        
       else{
          beforeRemove = findBeforeRemove(name,root);
         

          if(beforeRemove->getRight()->getEntry()->getName() == name){
              beforeRightmostLeft = findBeforeRightmostLeft(beforeRemove->getRight());
              rightSide = true;
              cout <<"lol";
          }
          else{
              beforeRightmostLeft = findBeforeRightmostLeft(beforeRemove->getLeft());
              rightSide = false;
              cout <<"???";
          }
          if(rightSide){
              removePoint = beforeRemove->getRight();
              temp1 = removePoint->getLeft();
              temp2 = removePoint->getRight();
              
              rightmostLeft = beforeRightmostLeft->getRight();
              beforeRightmostLeft->setRight(rightmostLeft->getLeft());
              
              beforeRemove->setRight(rightmostLeft);
              rightmostLeft->setLeft(temp1);
              rightmostLeft->setRight(temp2);
              
              removePoint->deleteNode();
              delete removePoint;
              
          }
          else{
              removePoint = beforeRemove->getLeft();
              temp1 = removePoint->getLeft();
              temp2 = removePoint->getRight();
              
              rightmostLeft = beforeRightmostLeft->getRight();
              beforeRightmostLeft->setRight(rightmostLeft->getLeft());
              
              beforeRemove->setLeft(rightmostLeft);
              rightmostLeft->setLeft(temp1);
              rightmostLeft->setRight(temp2);
              
              removePoint->deleteNode();
              delete removePoint;
          }
         
          
     }  
        return true;
     
    }
    
    else
        return false;
}
TreeNode* TreeDB::findBeforeRemove(string name, TreeNode* curNode){
    if(curNode!= NULL){
    if(curNode->getLeft()!=NULL){
        
        if(curNode->getLeft()->getEntry()->getName() == name)
        return curNode;
    }
    else if (curNode->getRight()!=NULL){
         
       
            
        if(curNode->getRight()->getEntry()->getName() == name){
          
        return curNode;
        }
    }
        
    else{
        if(curNode->getEntry()->getName() < name)
           return findRecursiveNode(name, curNode->getRight());
        else
           return findRecursiveNode(name,curNode->getLeft());
    }
    }
    return NULL;
}
TreeNode* TreeDB::findBeforeRightmostLeft(TreeNode* curNode){
   if(curNode!= NULL){
       if(curNode->getRight()!= NULL){
        if (curNode->getRight()->getRight()!= NULL)
            return findBeforeRightmostLeft(curNode->getRight());
        else 
            return curNode;
       }
   }
   else 
        return NULL;
}

// deletes all the entries in the database.
void  TreeDB::clear(){
    clearRecursive(root);
    root = NULL;
    
    
}

void TreeDB::clearRecursive(TreeNode* curNode){
   if(curNode!=NULL){
    if(curNode->getLeft() != NULL)
       clearRecursive(curNode->getLeft());
    if (curNode->getRight() != NULL)
       clearRecursive(curNode->getRight());
    curNode->deleteNode();
    delete curNode;
    }
}

// prints the number of probes stored in probesCount
void  TreeDB::printProbes(string _name) {
    if(find(_name)!= NULL){
        cout<<probesCount<<endl;
    }
    else 
        cout << "Error entry does not exist" << endl;
        
}
void TreeDB::printall(){
    if (root != NULL)
        printallRecursive(root);
}
void TreeDB::printallRecursive(TreeNode* curNode){
    if(curNode !=NULL){
    
      printallRecursive(curNode->getLeft());
      curNode->getEntry()->print();
    
    
        printallRecursive(curNode->getRight());
      
    
    
    }
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).


