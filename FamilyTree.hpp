#include <iostream>
namespace family{

    class node{
    public:
        std::string name;
        int gender;
        int level;
        node *mother, *father;
        node(std::string name);
    };
    

    class Tree{
    private:

        node* search(std::string name);
        node* search(node* root, std::string name);
        node* searchRelation(node* root, std::string name);
		void print(node* root, std::string name, int level);
        void removeNode(node* root);
        node* removeNode(node* root, std::string name);

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