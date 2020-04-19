#include <iostream>
namespace family{

    class node{
    public:
        std::string name;
        int gender;
        int level;
		bool del;
        node *mother, *father;
        node(std::string name);
    };
    

    class Tree{
    private:

        void removeTree(node* n);
        node* search(std::string name);
        node* search(node* root, std::string name);
        node* searchRelation(node* root, std::string name);
        void removeNode(node* ptr);
        void removeFindNode(node* ptr);
		void inorder(node* root);

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