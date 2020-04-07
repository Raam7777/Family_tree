#include "FamilyTree.hpp"
#include "doctest.h"
#include <iostream>
#include <string>
using namespace std;
using namespace family;

Tree buildTree(){
    Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
     return T;

}

TEST_CASE("Related function"){
    Tree T = buildTree();
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("Raam") == string("unrelated"));
    
    

}
TEST_CASE("Find function"){
     Tree T = buildTree();
     CHECK(T.find("father") == string("Yaakov"));
     CHECK(T.find("grandfather") == string("Isaac"));
     T.addMother("Isaac","Sara");
     CHECK(T.find("great-grandmother") == string("sara"));
     CHECK(T.find("great-great-grandfather") == string("Terah"));
    
}

TEST_CASE("AddFather function"){//האם כשמוסיפים אבא אז אם כרר יש לו אבא זה זורק שגיאה (אותו דרר לגבי אמא )

}

TEST_CASE("AddMother function"){

}

TEST_CASE("Remove function"){//האם כשמוחקים מישוו זה מוחק גם את ההורים ואי אפשר למצוא 

}