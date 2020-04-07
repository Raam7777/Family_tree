#include <iostream>

#include "FamilyTree.hpp"

using namespace std;
using namespace family;


Tree::Tree(std::string root){
    node* new_node = new node();

}

Tree::~Tree(){
   
}

Tree& Tree::addFather(string son, string father){

    return *this;
}
Tree& Tree::addMother(string son, string mother){
    return *this;
}
string Tree::relation(string name){
    return " ";
}
string Tree::find(string relation){
    return " ";
}
void Tree::display(){

}
void Tree::remove(string name){

}