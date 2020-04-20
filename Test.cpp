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
   // CHECK_THROWS(T.relation("Yaakov") == string("grandfather"));
   // CHECK_THROWS(T.relation("Rachel") == string("father"));
   // CHECK_THROWS(T.relation("Isaac") == string("grandmother"));
   // CHECK_THROWS(T.relation("Terah") == string("father"));
   // CHECK_THROWS(T.relation("Rivka") == string("great-great-grandmother"));
   // CHECK_THROWS(T.relation("Avraham") == string("great-great-grandfather"));
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

/*TEST_CASE("Remove function"){//21
    Tree T = buildTree();
/*	
    T.remove("Yosef");
    CHECK(T.relation("Yaakov") == string("unrelated"));
    CHECK( T.relation("Rachel") == string("unrelated"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("unrelated"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));



*/	/*
    T.remove("Isaac");
    CHECK( T.relation("Yaakov") == string("father"));
    CHECK( T.relation("Rachel") == string("mother"));
    CHECK( T.relation("Isaac") == string("unrelated"));
    CHECK( T.relation("Rivka") == string("grandmother"));
    CHECK( T.relation("Avraham") == string("unrelated"));
    CHECK( T.relation("Terah") == string("unrelated"));
    CHECK_THROWS(T.remove(" "));
    CHECK_THROWS(T.remove("sara"));
    CHECK_THROWS(T.remove("hava"));
	
	
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
    CHECK_THROWS(T.remove(" "));
    CHECK_THROWS(T.remove("ana"));
    CHECK_THROWS(T.remove("ruti"));
	

}*/

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

TEST_CASE("Reference add Tree case") { 
	family::Tree T ("Yosef");
	T.addFather("Yosef", "Yaakov")
	 .addMother("Yosef", "Rachel")
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
}

TEST_CASE("Yosef Tree case") {  
	// Add test case
	family::Tree T ("Yosef");
	T.addFather("Yosef", "Yaakov");
	T.addMother("Yosef", "Rachel");
	CHECK_THROWS(T.addFather("Yosef", "Yaakov")); // duplicate father
	CHECK_THROWS(T.addMother("Yosef", "Rivka"));  // duplicate mother
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Rachel", "Avi");
	T.addMother("Rachel", "Ruti");
	T.addFather("Isaac", "Avraham");
	T.addMother("Isaac", "Ruti");
	CHECK_THROWS(T.addFather("Isaac", "Israel"));  // duplicate father
	CHECK_THROWS(T.addMother("Isaac", "Ruti"));    // duplicate mother
	T.addFather("Avraham", "Yosi");
	T.addMother("Avraham", "Shelly");
	T.addFather("Avi", "Israel");
	T.addMother("Avi", "Sara");
	CHECK_THROWS(T.addFather("Avraham", "Avraham"));    // duplicate father
	CHECK_THROWS(T.addMother("Avraham", "Sara"));       // duplicate mother
	 
	// Relation test case
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.relation("Rachel") == string("mother"));
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.relation("Rivka") == string("grandmother"));
	CHECK(T.relation("Avi") == string("grandfather"));
	CHECK((T.relation("Ruti") == string("grandmother") || T.relation("Ruti") == string("great-grandmother")));
	CHECK(T.relation("Avraham") == string("great-grandfather"));
	CHECK((T.relation("Ruti") == string("grandmother") || T.relation("Ruti") == string("great-grandmother")));
	CHECK(T.relation("Israel") == string("great-grandfather"));
	CHECK(T.relation("Sara") == string("great-grandmother"));
	CHECK(T.relation("Yosi") == string("great-great-grandfather"));
    CHECK(T.relation("Shelly") == string("great-great-grandmother"));

    CHECK(T.relation("xyz") == string("unrelated"));
	CHECK(T.relation("Omer") == string("unrelated"));
	CHECK(T.relation("Ariel") == string("unrelated"));
	CHECK(T.relation(" ") == string("unrelated"));
	CHECK(T.relation("  Ariel") == string("unrelated"));

	// Find test case
	CHECK(T.find("father") == string("Yaakov"));
	CHECK(T.find("mother") == string("Rachel"));
	CHECK((T.find("grandfather") == string("Isaac") || T.find("grandfather") == string("Avi")));
	CHECK((T.find("grandmother") == string("Rivka") || T.find("grandmother") == string("Ruti")));
	CHECK((T.find("great-grandmother") == string("Sara") || T.find("great-grandmother") == string("Ruti")));
	CHECK((T.find("great-grandfather") == string("Avraham") || T.find("great-grandfather") == string("Israel")));
	CHECK(T.find("great-great-grandfather") == string("Yosi"));
	CHECK(T.find("great-great-grandmother") == string("Shelly"));

	CHECK_THROWS(T.find("grandfatrher"));
	CHECK_THROWS(T.find("great"));
	CHECK_THROWS(T.find(" "));
	CHECK_THROWS(T.find("   great"));
	CHECK_THROWS(T.find("grandfatrher   "));
	CHECK_THROWS(T.find("great,great,grandmother"));
	CHECK_THROWS(T.find("great?grandmother"));
	CHECK_THROWS(T.find("great grandmother"));

	// Remove test case
	//CHECK_THROWS(T.remove("Yosef"));  // removing the root is an error
	CHECK_THROWS(T.remove(" "));      // removing a non-existent person
	CHECK_THROWS(T.remove("xyz"));
	CHECK_THROWS(T.remove("Ariel"));
	CHECK_THROWS(T.remove("  Rivka"));

	T.remove("Yosi");  // remove the great-great-grandfather
	CHECK_THROWS(T.find("great-great-grandfather"));  // A removed relation does not exist
	T.addFather("Avraham", "Ido");  // Add a new father after removal
	T.remove("Avi");
	CHECK_THROWS(T.addFather("Avi", "Israel"));  // add to a removed person
	T.addFather("Rachel", "Shmual");
	T.remove("Isaac");
	T.remove("Rivka");
	T.remove("Ruti");
	CHECK_THROWS(T.find("grandmother"));
	CHECK_THROWS(T.addFather("Isaac", "Avraham"));
	CHECK_THROWS(T.addMother("Isaac", "Ruti"));
	CHECK_THROWS(T.addFather("Rivka", "Israel"));
	CHECK_THROWS(T.addMother("Rivka", "Sara"));
	T.remove("Yaakov");  // remove father
	T.remove("Rachel");  // remove mother
	CHECK_THROWS(T.find("father"));
	CHECK_THROWS(T.find("mother"));
	CHECK_THROWS(T.addFather("Yaakov", "Avraham"));   // add to non-existent person
	CHECK_THROWS(T.addMother("Yaakov", "Ruti"));      // add to non-existent person
	CHECK_THROWS(T.addFather("Rachel", "Avraham"));   // add to non-existent person
	CHECK_THROWS(T.addMother("Rachel", "Ruti"));      // add to non-existent person
}



