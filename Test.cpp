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

TEST_CASE("Related function"){//13
    Tree T = buildTree();
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("grandfather"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("great-grandfather"));
    CHECK( T.relation("Terah") == string("great-great-grandfather"));
    CHECK( T.relation("Raam") == string("unrelated"));
    CHECK_THROWS(T.relation("Yaakov") == string("grandfather"));
    CHECK_THROWS(T.relation("Rachel") == string("father"));
    CHECK_THROWS(T.relation("Isaac") == string("grandmother"));
    CHECK_THROWS(T.relation("Terah") == string("father"));
    CHECK_THROWS(T.relation("Rivka") == string("great-great-grandmother"));
    CHECK_THROWS(T.relation("Avraham") == string("great-great-grandfather"));
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
	CHECK(T.find("father") == string("RachelF"));
	CHECK(T.relation("RachelF") == string("father"));
	CHECK_THROWS(T.addFather("Isaac", "IsaacF"));
	T.addFather("Rivka", "RivkaF");
	CHECK(T.find("father") == string("RivkaF"));
	CHECK(T.relation("RivkaF") == string("father"));
	CHECK_THROWS(T.addFather("Rivka", "RivkaFather"));
	CHECK_THROWS(T.addFather("Yosef", "YosefF"));
	T.addFather("Terah", "TerahF");
	CHECK(T.find("father") == string("TerahF"));
	CHECK(T.relation("TerahF") == string("father"));
}

TEST_CASE("AddMother function"){//10
	Tree T = buildTree();
	CHECK_THROWS(T.addMother("yaakov", "yaakovM"));
	T.addMother("Rachel", "RachelM");
	CHECK(T.find("mother") == string("RachelM"));
	CHECK(T.relation("RachelM") == string("mother"));
	CHECK_THROWS(T.addMother("Yosef", "YosefM"));
	T.addMother("Rivka", "RivkaM");
	CHECK(T.find("mother") == string("RivkaM"));
	CHECK(T.relation("RivkaM") == string("mother"));
	CHECK_THROWS(T.addMother("Rivka", "RivkaMother"));
	CHECK_THROWS(T.addMother("Yosef", "YosefM"));
	T.addMother("Terah", "TerahM");
	CHECK(T.find("mother") == string("TerahM"));
	CHECK(T.relation("TerahM") == string("mother"));
}

TEST_CASE("Remove function"){//21
    Tree T = buildTree();
    T.remove("Yosef");
    CHECK( T.relation("Yaakov") == string("unrelated"));
    CHECK( T.relation("Rachel") == string("unrelated"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("unrelated"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
    CHECK_THROWS(T.remove("Yaakov"));
    CHECK_THROWS(T.remove("Rachel"));
    CHECK_THROWS(T.remove("Isaac"));
    CHECK_THROWS(T.remove("Rivka"));
    CHECK_THROWS(T.remove("Avraham"));
    CHECK_THROWS(T.remove("Terah"));

    T = buildTree();
    T.remove("Isaac");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("unrelated"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
    CHECK_THROWS(T.remove("Isaac"));
    CHECK_THROWS(T.remove("Rivka"));
    CHECK_THROWS(T.remove("Avraham"));
    CHECK_THROWS(T.remove("Terah"));


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
    CHECK_THROWS(T.remove("milka"));
    CHECK_THROWS(T.remove("haran"));
    CHECK_THROWS(T.remove("sara"));


}

TEST_CASE("new tree function"){
    Tree T ("Yosef");
    T.addFather("Yosef","Yaakov").addFather("Yaakov","Isaac").addFather("Isaac","Avraham").addFather("Avraham","Terah");
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

