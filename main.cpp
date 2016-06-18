#include <iostream>
#include "BSTree.h"

//comparators of int type
struct compare_int_e {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

struct compare_int_l {
	bool operator()(int a, int b) const {
		return a<b;
	}
};

//comparators of string type
struct compare_string_e {
	bool operator()(const std::string &a, const std::string &b) const {
		return ucase(a)==ucase(b);
	}

	private:
	std::string ucase(const std::string &str) const {
		std::string tmp(str);
		for(int i=0; i< tmp.size(); ++i)
			tmp[i]=std::toupper(tmp[i]);
	
		return tmp;
	}	
};

struct compare_string_l {
	bool operator()(const std::string &a, const std::string &b) const {
		return ucase(a) < ucase(b);
	}

	private:
	std::string ucase(const std::string &str) const {
		std::string tmp(str);
		for(int i=0; i< tmp.size(); ++i)
			tmp[i]=std::toupper(tmp[i]);
	
		return tmp;
	}	
};	

//custom struct
struct test_struct{
		int i;
		char c;
		double d;

		test_struct(const int &in, const char &ch, const double &dob) : i(in), c(ch), d(dob){}

		bool operator<(const test_struct& s) const {
      		return s.i < this->i;
  		}

  		bool operator==(const test_struct& s) const {
      		return s.i == this->i;
  		}

		~test_struct(){
		}
	};

	std::ostream& operator<<(std::ostream &os, const test_struct &s) {
			return os << s.i << " " << s.c << " " << s.d << std::endl;
			
		}

//comparator for custom struct
struct compare_struct_l {
	bool operator()(test_struct a, test_struct b) const {
		return a < b;
	}
};

struct compare_struct_e {
	bool operator()(test_struct a, test_struct b) const {
		return a == b;
	}
};






void test_1(){

	 bstree<int, compare_int_e, compare_int_l> sapo_tree;

	 std::cout << sapo_tree;

	 try{
	 	
	 	sapo_tree.add(3);
	 	sapo_tree.add(4);
	 	sapo_tree.add(5);
	 	sapo_tree.add(-1);
	 	sapo_tree.add(3*5);
	 	std::cout << sapo_tree << std::endl;

	 

	 } catch (...) {

	 	std::cout << "presa eccezione" << std::endl;
	}



	 std::cout << "size: " << sapo_tree.get_size() << std::endl;

	 std::cout << sapo_tree << std::endl;
	 sapo_tree.delete_node(3);
	 std::cout << sapo_tree << std::endl;

	 sapo_tree.check(3);
	 std::cout << sapo_tree << std::endl;

	 //-------------------------------------------------------

	 bstree<int, compare_int_e, compare_int_l> sub;
	 sub = subtree(sapo_tree, 4);

	 std::cout << "subtree 4: " << std::endl << sub << std::endl;

	 sub = subtree(sapo_tree, -1);

	 std::cout << "subtree -1: " << std::endl << sub << std::endl;

	 sub = subtree(sapo_tree, 5);

	 std::cout << "subtree 5: " << std::endl << sub << std::endl;

	 sub = subtree(sapo_tree, 15);

	 std::cout << "subtree 15: " << std::endl << sub << std::endl;

	 //----------------------------------------------------------

	 bstree<int, compare_int_e, compare_int_l> badass_tree;

	 std::cout << "badass" << std::endl << badass_tree << std::endl;

	 badass_tree.add(3);
	 badass_tree.add(2);
	 badass_tree.add(1);

	 std::cout << "badass" << std::endl << badass_tree << std::endl;

	 badass_tree.delete_node(3);

	 std::cout << "badass" << std::endl << badass_tree << std::endl;

	 bstree<int, compare_int_e, compare_int_l> badass2_tree;

	 std::cout << "badass2" << std::endl << badass2_tree << std::endl;

	 badass2_tree.add(5);
	 badass2_tree.add(2);
	 badass2_tree.add(1);
	 badass2_tree.add(3);
	 badass2_tree.add(4);

	 std::cout << "badass2" << std::endl << badass2_tree << std::endl;

	 badass2_tree.delete_node(3);

	 std::cout << "badass2" << std::endl << badass2_tree << std::endl;

	 //clear

	 sapo_tree.clear();

	 std::cout << "after clear: " << std::endl << sapo_tree << std::endl;

	 std::cout << sapo_tree.check(4) << std::endl;

	 std::cout << sapo_tree.get_size();

	
}

//Test con T int
void test_2(){
	std::cout << "*** Start of test_2 with type INT ***" << std::endl;
	//instantiation of a bstree
	bstree<int, compare_int_e, compare_int_l> tree;

	std::cout << "Add nodes test with insertion of duplicated value (4)" << std::endl;

	//add a node test
	try{
		tree.add(2);
		tree.add(1);
		tree.add(0);
		tree.add(4);
		tree.add(5);
		tree.add(3);
		tree.add(6);
		tree.add(4);//duplicated value
	}catch(duplicated_value &e){
		std::cout << e.what();
	} 

	//instantiation of a forward const iterator
	bstree<int, compare_int_e, compare_int_l>::const_iterator i, ie;

	i = tree.begin();
	ie = tree.end();
	
	//print a bstree test
	std::cout << "Print of tree after insertion of elements" << std::endl;
	std::cout << tree;

	//return the size of a bstree test
	std::cout << "size of the tree: " << tree.get_size() << std::endl;

	//check the existence of a value present in the bstree
	std::cout << "test to check existence of value (4): " << tree.check(4) << std::endl;

	//check the existence of a value NOT present in the bstree
	std::cout << "test to check existence of value (7): " << tree.check(7) << std::endl;

	//copy constructor of a bstree test
	bstree<int, compare_int_e, compare_int_l> other(tree);
	std::cout << "test of the initialization of a tree by copy" << std::endl << other;
	other.clear();
	std::cout << "test of the deletion of a copied tree" << std::endl << other;

	//assignement of a bstree test
	bstree<int, compare_int_e, compare_int_l> to_assign;

	to_assign.add(5);
	to_assign.add(4);
	to_assign.add(2);
	to_assign.add(7);
	std::cout << "instantiation of a tree to_assign" << std::endl << to_assign;

	tree = to_assign;

	std::cout << "test the assignement of to_assign to the previous tree" << std::endl << tree;

	//delete a node leaf of the bstree test
	to_assign.delete_node(7);


	std::cout << "test of the deletion of value (7)" << std::endl << to_assign;

	//test of get minimum
	bstree<int, compare_int_e, compare_int_l> another_tree;

	another_tree.add(10);
	another_tree.add(8);
	another_tree.add(9);
	another_tree.add(7);
	another_tree.add(12);
	another_tree.add(13);
	another_tree.add(11);

	std::cout << "another tree instantiation" << std::endl << another_tree;

	//test deletion

	bstree<int, compare_int_e, compare_int_l> deletion_tree;

	deletion_tree.add(50);
	deletion_tree.add(30);
	deletion_tree.add(40);
	deletion_tree.add(60);
	deletion_tree.add(70);
	deletion_tree.add(20);
	deletion_tree.add(90);
	deletion_tree.add(550);
	deletion_tree.add(35);
	deletion_tree.add(37);

	std::cout << "try delete" << std::endl;

	deletion_tree.delete_node(30);

	std::cout << "after deletion of (30) from deletion_tree " << std::endl << deletion_tree;

	std::cout << "another tree: " << std::endl << another_tree << std::endl;

	another_tree.delete_node(8);
	another_tree.delete_node(12);

	std::cout << "after deletion of (12) from another_tree" << std::endl << another_tree;

	//test of clear bstree
	//delete &another_tree;

	std::cout << "after clear of another_tree" << std::endl << another_tree;

	std::cout << "test of subtree" << std::endl;
	//test of subtree
	bstree<int, compare_int_e, compare_int_l> subtree_test;

	subtree_test.add(13);
	subtree_test.add(9);
	subtree_test.add(12);
	subtree_test.add(5);
	subtree_test.add(10);
	subtree_test.add(11);
	subtree_test.add(4);
	subtree_test.add(15);
	subtree_test.add(14);
	subtree_test.add(16);


	
	std::cout << "print of subtree_test: " << std::endl << subtree_test << std::endl;

	bstree<int, compare_int_e, compare_int_l> sub = subtree(subtree_test, 10); 
	std::cout << "print of subtree with root (10)" << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 12); 
	std::cout << "print of subtree with root (12)" << std::endl << sub << std::endl;
	
	sub = subtree(subtree_test, 15); 
	std::cout << "print of subtree with root (15)" << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 11); 
	std::cout << "print of subtree with root (11)" << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 13); 
	std::cout << "print of subtree with root (13)" << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 9); 
	std::cout << "print of subtree with root (9)" << std::endl << sub << std::endl;

	//test di subtree con elemento non esistente nell'albero

	try{
		std::cout << "test of subtree with non existing root (0)" << std::endl;
		sub = subtree(subtree_test, 0); 
		std::cout << "print of subtree " << std::endl << sub << std::endl;
	}catch(non_existent_value &e){
		std::cout << e.what() << std::endl;
	}
	
	//test of is_leaf
	std::cout << "(9) is leaf? " << another_tree.is_leaf(9) << std::endl;
	std::cout << "(10) is leaf? " << another_tree.is_leaf(10) << std::endl;


}


//Test con T stringa
void test_3(){
	std::cout << "*** Start of test_3 with type STRING ***" << std::endl;

	bstree<std::string, compare_string_e, compare_string_l> string_tree;

	string_tree.add("bbbbbbb");
	string_tree.add("aaaa");
	string_tree.add("chndkah");
	string_tree.add("pluto");
	string_tree.add("pippo");
	

	std::cout << "print of string_tree" << std::endl << string_tree << std::endl;


	string_tree.delete_node("pluto");


	std::cout << "print of string_tree after deletion of (pluto)" << std::endl << string_tree << std::endl;

	string_tree.add("pluto");

	std::cout << "print of string_tree after add of (pluto)" << std::endl << string_tree << std::endl;

	string_tree.delete_node("aaaa");

	std::cout << "print of string_tree after deletion of (aaaa)" << std::endl << string_tree << std::endl;

	bstree<std::string, compare_string_e, compare_string_l> copy_string_tree(string_tree);

	std::cout << "print of copy_string_tree" << std::endl << string_tree << std::endl;

	copy_string_tree.clear();

	string_tree.clear();

	std::cout << "print of string_tree after clear" << std::endl << string_tree << std::endl;

	std::cout << "print of copy_string_tree after clear" << std::endl << copy_string_tree << std::endl;

	copy_string_tree.add("prova");

	bstree<std::string, compare_string_e, compare_string_l>::const_iterator i, ie;

	i = copy_string_tree.begin();
	ie = copy_string_tree.end();

	while(i != ie){
		std::cout << ("iteration") << std::endl;
		++i;
	}

}

//Test con T struct
void test_4(){
	std::cout << "*** Start of test_4 with custom type TEST_STRUCT ***" << std::endl;
	bstree<test_struct, compare_struct_e, compare_struct_l> struct_tree;

	test_struct s(5, 'a', 0.1);

	std::cout << "add of test_struct s(5, 'a', 0.1) to struct_tree" << std::endl;

	struct_tree.add(s);
	
	std::cout << "print of struct_tree " << std::endl << struct_tree << std::endl;

	std::cout << "check of s" << std::endl << struct_tree.check(s) << std::endl;

	struct_tree.delete_node(s);
	//struct_tree.clear();

	std::cout << "print of struct_tree " << std::endl << struct_tree << std::endl;

	std::cout << "print of tree size " << std::endl << struct_tree.get_size() << std::endl;

	std::cout << "Test of copy constructor with new tree copy_struct_tree" << std::endl; 
	bstree<test_struct, compare_struct_e, compare_struct_l> copy_struct_tree(struct_tree);
	std::cout << "Print of copy_struct_tree" << std::endl << copy_struct_tree << std::endl;

	test_struct s1(7, 'b', 2.7);
	test_struct s2(9, 'c', -3.5);

	struct_tree.add(s);
	struct_tree.add(s1);
	struct_tree.add(s2);

	//Test of operator ->
	bstree<test_struct, compare_struct_e, compare_struct_l>::const_iterator i, ie;

	i = struct_tree.begin();
	ie = struct_tree.end();

	while(i != ie){
		std::cout << i->c << std::endl;
		++i;
	}

}



int main(){
    test_1();
    test_2();
    test_3();
    test_4();

	return 0;
}