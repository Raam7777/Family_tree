#include <iostream>
namespace family{
    class Tree{
        
    public:
        struct node {
            std::string data;
            struct node *mother, *father;
        };
        node *T_root;

        Tree(std::string root);
        ~Tree();

        Tree& addFather(std::string son, std::string father);
        Tree& addMother(std::string son, std::string mother);
        std::string relation(std::string name);
        std::string find(std::string relation);
        void display();
        void remove(std::string name);
    };
};