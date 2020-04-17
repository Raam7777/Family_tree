#include <iostream>
namespace family{

    class node{
    public:
        std::string name;
        node *mother, *father;
        node(std::string name);
    };
    

    class Tree{
    private:

        void removeTree(node* n);
        node* search(std::string name);
        node* search(node* root, std::string name);
        void removeNodeFather(node* ptr, std::string name);
        void removeNodeMother(node* ptr, std::string name);

    public:
        
        node *root;

        Tree(std::string name);
        ~Tree();

        Tree& addFather(std::string son, std::string father);
        Tree& addMother(std::string son, std::string mother);
        std::string relation(std::string name);
        std::string find(std::string relation);
        void display();
        void remove(std::string name);
        
    };
};