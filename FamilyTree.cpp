#include <iostream>

#include "FamilyTree.hpp"

using namespace std;
using namespace family;

node::node(string name){
    this->name = name;
    this->father = nullptr;
    this->mother = nullptr;
}

Tree::Tree(string name){
    this->root = new node(name);

}

Tree::~Tree(){
   removeTree(root);
}

void Tree::removeTree(node* n){
    /*
    if(n != nullptr){
        removeTree(n->mother);
        removeTree(n->father);
        delete n;
    }
    */
}

node* Tree::search(string name){
    return search(this->root, name);
}

node* Tree::search(node* root, string name){

    if(root==nullptr){
        return nullptr;
    }

    if(root->name.compare(name)==0){
        return root;
    }

    node* sf = search(root->father, name);
    if(sf != nullptr){
        return sf;    
    }

    node* sm = search(root->mother, name);
    if(sm != nullptr){
            return sm;   
    }

    return nullptr;
    
}

Tree& Tree::addFather(string son, string father){
    
    node* searchSon = search(this->root, son);
    
    if(searchSon == nullptr){
        throw invalid_argument("The son does not exist");
    }

    if(searchSon->father == nullptr){
        searchSon->father = new node(father);
        return *this;
    }
    else{
        throw invalid_argument("The father already exists");
    }
    

    
   
}
Tree& Tree::addMother(string son, string mother){
    
    node* searchSon = search(this->root, son);
    
    if(searchSon == nullptr){
        throw invalid_argument("The son does not exist");
    }

    if(searchSon->mother == nullptr){
        searchSon->mother = new node(mother);
        return *this;
    }
    else{
        throw invalid_argument("The mother already exists");
    }
   
}
string Tree::relation(string name){
    return " ";
}
string Tree::find(string relation){
    return " ";
}
void Tree::display(){

}

void Tree::removeNodeFather(node* ptr, string name){
    
    if(ptr != nullptr){
        if(ptr->father != nullptr){
            if(ptr->father->name.compare(name)){
                removeNodeFather(ptr->father, name);
            }
        }    
    }
    
}

void Tree::removeNodeMother(node* ptr, string name){
    
    if(ptr != nullptr){
        if(ptr->mother != nullptr){
            if(ptr->mother->name.compare(name)){
                removeNodeMother(ptr->mother, name);
            }
        }    
    }
   
}

void Tree::remove(string name){
/*
    node* findName = search(root, name);
    if(findName == nullptr){
        throw invalid_argument("The name does not exist");
    }
    else{
        
        if(findName->father->name.compare(name)==0){
            delete findName->father;
            findName->father = nullptr;
        }

        if(findName->father->name.compare(name)==0){
            delete findName->mother;
            findName->mother = nullptr;
        }
    }
*/
}