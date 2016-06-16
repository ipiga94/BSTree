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

/*struct compare_struct_l {
	bool operator()(test_struct a, test_struct b) const {
		return a.i < b.i;
	}
};

struct compare_struct_e {
	bool operator()(test_struct a, test_struct b) const {
		return a.i == b.i;
	}
};

struct test_struct{
		int i;
		char c;
		double d;

		test_struct(int &in, char &ch, double &dob) : i(in), c(ch), d(dob){}

		~test_struct(){}
	};*/




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

void test_2(){

	//instantiation of a bstree
	bstree<int, compare_int_e, compare_int_l> tree;

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
	}catch(...){
		std::cout << "generated duplicated key exception" << std::endl;
	}

	//instantiation of a forward const iterator
	bstree<int, compare_int_e, compare_int_l>::const_iterator i, ie;

	i = tree.begin();
	ie = tree.end();
	
	//print a bstree test
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


	
	std::cout << "stampa di subtree_test: " << std::endl << subtree_test << std::endl;

	bstree<int, compare_int_e, compare_int_l> sub = subtree(subtree_test, 10); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 12); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;
	
	sub = subtree(subtree_test, 15); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 11); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 13); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;

	sub = subtree(subtree_test, 9); 
	std::cout << "stampo subtree " << std::endl << sub << std::endl;

	//sub = subtree(subtree_test, 0); 
	//std::cout << "stampo subtree " << std::endl << sub << std::endl;

	//test of is_leaf
	std::cout << another_tree.is_leaf(9) << std::endl;
	std::cout << another_tree.is_leaf(10) << std::endl;


}

void test_3(){
	bstree<int, compare_int_e, compare_int_l> tree;

	try{

		tree.add(50);
		tree.add(60);
		tree.add(30);
		tree.add(40);
		tree.add(20);
		tree.add(70);
		tree.add(20);

	}catch(duplicated_value &e){
		std::cout << e.what();
	} 

	bstree<int, compare_int_e, compare_int_l> copy_tree(tree);

	std::cout << copy_tree;

	

	bstree<std::string, compare_string_e, compare_string_l> string_tree;

	string_tree.add("bbbbbbb");
	string_tree.add("aaaa");
	string_tree.add("chndkah");
	string_tree.add("pluto");
	string_tree.add("pippo");
	

	std::cout << "stampa di string_tree" << std::endl << string_tree << std::endl;


	string_tree.delete_node("pluto");


	std::cout << "stampa di string_tree dopo cancellazione di (pluto)" << std::endl << string_tree << std::endl;

	string_tree.add("pluto");

	std::cout << "stampa di string_tree dopo aggiunta di (pluto)" << std::endl << string_tree << std::endl;

	string_tree.delete_node("aaaa");

	std::cout << "stampa di string_tree dopo cancellazione di (aaaa)" << std::endl << string_tree << std::endl;

	bstree<std::string, compare_string_e, compare_string_l> copy_string_tree(string_tree);

	std::cout << "stampa di copy_string_tree" << std::endl << string_tree << std::endl;

	copy_string_tree.clear();

	string_tree.clear();

	std::cout << "stampa di string_tree dopo clear" << std::endl << string_tree << std::endl;

	std::cout << "stampa di copy_string_tree dopo clear" << std::endl << copy_string_tree << std::endl;

	copy_string_tree.add("prova");

	bstree<std::string, compare_string_e, compare_string_l>::const_iterator i, ie;

	i = copy_string_tree.begin();
	ie = copy_string_tree.end();

	while(i != ie){
		std::cout << ("itero") << std::endl;
		++i;
	}

}

int main(){
    test_1();
    test_2();
    test_3();

	return 0;
}