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
    this->root = new node(name);

}

Tree::~Tree(){
   removeTree(root);
}

void Tree::removeTree(node* n){
    
    if(n != nullptr){
        removeTree(n->mother);
        removeTree(n->father);
        delete n;
    }
    
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

void Tree::inorder(node* root) {
	if (root != nullptr) {
		inorder(root->father);
		cout << root->name << ",";
		inorder(root->mother);
	}
}

void Tree::display(){
	inorder(this->root);
	cout << endl;
}

void Tree::removeNode(node* ptr){
    int i=0;
    cout<<1;
    Tree* tree;

    if(ptr->father == nullptr && ptr->mother == nullptr){
        cout<<5;
        ptr=nullptr;
        tree = new Tree(ptr->name);
        delete ptr;
        cout<<6;
        
    }   
    
    else{
        if(ptr->father != nullptr){
                cout<<2;
                removeNode(ptr->father);
            
        }
        if(ptr->mother != nullptr){
                cout<<3;
                removeNode(ptr->mother);
        }
    }
    
}

void Tree::removeFindNode(node* root, string name){



}

void Tree::remove(string name){
    
    node* ptr = search(this->root,name);
    if(ptr == NULL){
        throw out_of_range("the name not exist");
    }
    else{
        removeNode(ptr);
    }
    return;

}