#include <iostream>
#include <string>

#include "FamilyTree.hpp"

using namespace std;
using namespace family;

node::node(string name){
    this->name = name;
    this->father = nullptr;
    this->mother = nullptr;
    this->gender = 0;
    this->level = 0;

}

Tree::Tree(string name){
    node* newNode = new node(name);
    this->root = newNode;
    this->root->father = nullptr;
    this->root->mother = nullptr;
    this->root->name = name;

}

Tree::~Tree(){
   
}


node* Tree::search(string name){
    return search(this->root, name);
}

node* Tree::search(node* root, string name){

    if(root==nullptr){
        return nullptr;
    }

    if(root->name == name){
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
        searchSon->father->gender = 1;
        searchSon->father->level = searchSon->level + 1;
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
        searchSon->mother->gender = 2;
        searchSon->mother->level = searchSon->level + 1;
        return *this;
    }
    else{
        throw invalid_argument("The mother already exists");
    }
   
}



string Tree::relation(string name){
    node* n = search(name);
    if(n == nullptr){
        return "unrelated";
    }
	else if (n->level == 0) {
		
		return "me";
	}
    else{
		
        if(n->level == 1 && n->gender == 1){
            return "father";
        }
        else if(n->level == 1 && n->gender == 2){
            return "mother";
        }
        else if(n->level == 2 && n->gender == 1){
            return "grandfather";
        }
        else if(n->level == 2 && n->gender == 2){
            return "grandmother";
        }
        else {
            string great = "";
            for(int i = 2; i < n->level; i++){
                great += "great-" ;
            }
            if(n->gender == 1){
                great = great + "grandfather";
            }
            if(n->gender == 2){
                great = great + "grandmother";
            }
            return great;
        }

    }
   
}

node* Tree::searchRelation(node* root, string name){

    if(root!=nullptr){
        
        if(relation(root->name) == name){
            return root;
        }

        node* s = searchRelation(root->father, name);
        if(s != nullptr) return s;
        else return searchRelation(root->mother, name);
    }
    else{
        return nullptr;
    }   
}

string Tree::find(string relation){
    node* _find = searchRelation(root, relation);
    if(_find == nullptr){
        throw invalid_argument("not found");
    }
    return _find->name;
}

void Tree::print(node* root, string name, int level) {
	if(root==nullptr){
        return;
    }
    print(root->father, root->name, root->level);
    print(root->mother, root->name, root->level);
    cout << root->name << "->"<< root->level<< "   |   ";
    if(root->name == name){
        cout<<endl;
    }
    

}

void Tree::display(){
	print(this->root,this->root->name,this->root->level);
	
}

void Tree::removeNode(node* root)
{
    if(root==NULL)
        return;

    if(root->father==NULL&&root->mother==NULL)
        delete(root);

    removeNode(root->father);
    removeNode(root->mother);
}

node* Tree::removeNode(node* root, string name)
{
    if(root==NULL)
        return NULL;

    if(root->name == name)
    {
        removeNode(root);
        return NULL;
    }

    root->father=removeNode(root->father,name);
    root->mother=removeNode(root->mother,name);
    return root;
    
}


void Tree::remove(string name){
   
    node* ptr = search(name);
    if(this->root->name == name){
        throw invalid_argument("not remove the root");
    }

    if(ptr == NULL){
        throw out_of_range("the name not exist");
    }

    this->root=removeNode(this->root,name);

}