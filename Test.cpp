
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
TEST_CASE("inorder") {
	Tree T = buildTree();
	//T.display();
}


TEST_CASE("Related function"){//13
    Tree T = buildTree();
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("Raam") == string("unrelated"));
   
}

TEST_CASE("Find function"){//13
    Tree T = buildTree();
    CHECK(T.find("father") == string("Yaakov"));
    CHECK(T.find("mother") == string("Rachel"));
    CHECK(T.find("grandfather") == string("Isaac"));
    CHECK(T.find("grandmother") == string("Rivka"));
    CHECK(T.find("great-grandfather") == string("Avraham"));
    CHECK(T.find("great-great-grandfather") == string("Terah"));
    CHECK_THROWS(T.find("brother"));
    CHECK_THROWS(T.find("sister"));
    CHECK_THROWS(T.find("great-great-grandmother"));
    CHECK_THROWS(T.find("great-great-great-grandfather"));
    CHECK_THROWS(T.find("great-great-great-grandmother"));
    CHECK_THROWS(T.find("great-great-great-great-grandfather"));
    CHECK_THROWS(T.find("great-great-great-great-grandmother"));
}

TEST_CASE("AddFather function"){ //10
	Tree T = buildTree();
	CHECK_THROWS(T.addFather("yaakov", "yaakovF"));
	T.addFather("Rachel", "RachelF");
	CHECK((T.find("grandfather") == string("RachelF") || T.find("grandfather") == string("Isaac")));
	CHECK(T.relation("RachelF") == string("grandfather"));
	CHECK_THROWS(T.addFather("Isaac", "IsaacF"));
	T.addFather("Rivka", "RivkaF");
	T.addFather("RivkaF", "RivkaFf");
	CHECK((T.find("great-grandfather") == string("RivkaF") || T.find("great-grandfather") == string("Avraham")));
	CHECK(T.relation("RivkaF") == string("great-grandfather"));
	CHECK_THROWS(T.addFather("Rivka", "RivkaFather"));
	CHECK_THROWS(T.addFather("Yosef", "YosefF"));
	T.addFather("Terah", "TerahF");
	CHECK(T.find("great-great-great-grandfather") == string("TerahF"));
	CHECK(T.relation("TerahF") == string("great-great-great-grandfather"));
}

TEST_CASE("AddMother function"){//10
	Tree T = buildTree();
	CHECK_THROWS(T.addMother("yaakov", "yaakovM"));
	T.addMother("Rachel", "RachelM");
	CHECK((T.find("grandmother") == string("RachelM") || T.find("grandmother") == string("Rivka")));
	CHECK(T.relation("RachelM") == string("grandmother"));
	CHECK_THROWS(T.addMother("Yosef", "YosefM"));
	T.addMother("Rivka", "RivkaM");
	CHECK(T.find("great-grandmother") == string("RivkaM"));
	CHECK(T.relation("RivkaM") == string("great-grandmother"));
	CHECK_THROWS(T.addMother("Rivka", "RivkaMother"));
	CHECK_THROWS(T.addMother("Yosef", "YosefM"));
	T.addMother("Terah", "TerahM");
	CHECK(T.find("great-great-great-grandmother") == string("TerahM"));
	CHECK(T.relation("TerahM") == string("great-great-great-grandmother"));
}

TEST_CASE("Remove function 1"){//21
    Tree T = buildTree();

	T.remove("Isaac");
	T.display();
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
    CHECK_THROWS(T.remove("Isaac"));
    CHECK_THROWS(T.remove("Avraham"));
    CHECK_THROWS(T.remove("Terah"));

}

TEST_CASE("Remove function 2") {
	Tree T = buildTree();
	T.addMother("Isaac", "sara");
	T.addMother("sara", "milka");
	T.addFather("sara", "haran");
	T.remove("sara");
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.relation("Rachel") == string("mother"));
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.relation("Rivka") == string("grandmother"));
	CHECK(T.relation("Avraham") == string("great-grandfather"));
	CHECK(T.relation("sara") == string("unrelated"));
	CHECK(T.relation("Terah") == string("great-great-grandfather"));
	CHECK(T.relation("haran") == string("unrelated"));
	CHECK(T.relation("milka") == string("unrelated"));
	CHECK_THROWS(T.remove("milka"));
	CHECK_THROWS(T.remove("haran"));
	CHECK_THROWS(T.remove("sara"));

}

TEST_CASE("new tree function"){
    Tree T ("Yosef");
    T.addFather("Yosef","Yaakov")
		.addFather("Yaakov","Isaac")
		.addFather("Isaac","Avraham")
		.addFather("Avraham","Terah");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("unrelated"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("unrelated"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("sara") == string("unrelated"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("haran") == string("unrelated"));
    CHECK( T.relation("milka") == string("unrelated"));
    CHECK(T.find("father").compare("Yaakov")==0);
    CHECK(T.find("grandfather").compare("Isaac")==0);
    CHECK(T.find("great-grandfather").compare("Avraham")==0);
    CHECK(T.find("great-great-grandfather").compare("Terah")==0);
    CHECK_THROWS(T.find("mother"));
    CHECK_THROWS(T.find("grandmother"));
    CHECK_THROWS(T.find("great-grandmother"));

    T.addMother("Yosef","Rachel").addMother("Yaakov","Rivka").addMother("Isaac","sara").addMother("sara","milka");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("sara") == string("great-grandmother"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("haran") == string("unrelated"));
    CHECK( T.relation("milka") == string("great-great-grandmother"));
    CHECK(T.find("father").compare("Yaakov")==0);
    CHECK(T.find("grandfather").compare("Isaac")==0);
    CHECK(T.find("great-grandfather").compare("Avraham")==0);
    CHECK(T.find("great-great-grandfather").compare("Terah")==0);
    CHECK(T.find("mother").compare("Rachel")==0);
    CHECK(T.find("grandmother").compare("Rivka")==0);
    CHECK(T.find("great-grandmother").compare("sara")==0);
    CHECK_THROWS(T.addFather("Yosef","Aviho"));
    CHECK_THROWS(T.addFather("Isaac","Avi"));
    CHECK_THROWS(T.addFather("Avraham","Yosef"));

}



