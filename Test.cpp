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
	 T.display();
     return T;

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

TEST_CASE("Remove function"){//57
    Tree T = buildTree();


    CHECK_THROWS(T.remove("Yosef"));
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));


	
    T.remove("Isaac");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
	CHECK_THROWS(T.find("great-grandfather"));
	CHECK_THROWS(T.find("great-great-grandfather"));
    CHECK_THROWS(T.remove(" "));
    CHECK_THROWS(T.remove("sara"));
    CHECK_THROWS(T.remove("hava"));

	T.remove("Yaakov");
	CHECK( T.relation("Yaakov") == string("unrelated"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("unrelated"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
	CHECK_THROWS(T.find("father"));
	CHECK_THROWS(T.find("grandfather"));
	CHECK_THROWS(T.find("grandmother"));
	CHECK_THROWS(T.find("great-grandfather"));
	CHECK_THROWS(T.find("great-great-grandfather"));
	
	
    T = buildTree();
    T.addMother("Isaac", "sara").addMother("sara", "milka").addFather("sara", "haran");
    T.remove("sara");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("sara") == string("unrelated"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("haran") == string("unrelated"));
    CHECK( T.relation("milka") == string("unrelated"));
	CHECK_THROWS(T.find("great-great-grandmother"));
	CHECK_THROWS(T.find("great-great-great-grandfather"));
	CHECK_THROWS(T.find("great-great-great-grandmother"));
    CHECK_THROWS(T.remove(" "));
    CHECK_THROWS(T.remove("ana"));
    CHECK_THROWS(T.remove("ruti"));
	CHECK_THROWS(T.remove(" rasa"));

	T.remove("Rachel");
	CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("unrelated"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("sara") == string("unrelated"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("haran") == string("unrelated"));
    CHECK( T.relation("milka") == string("unrelated"));
	CHECK_THROWS(T.find("mother"));
	CHECK_THROWS(T.find("great-great-grandmother"));
	CHECK_THROWS(T.find("great-great-great-grandfather"));
	CHECK_THROWS(T.find("great-great-great-grandmother"));

	T.remove("Avraham");
	CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("unrelated"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("sara") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));


	

}



