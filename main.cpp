//Ilaria Pigazzini 780684
//Programmazione e amministrazione di sistema 2016
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



//Test con T int
void test_1(){
	std::cout << "********** Start of test_1 with type INT **********" << std::endl;
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
	std::cout << "test of the initialization of a tree by copy" << std::endl << "print of the copied tree" << other;
	other.clear();
	std::cout << "test of the clear of the copied tree" << std::endl << other;

	//assignement of a bstree test
	bstree<int, compare_int_e, compare_int_l> to_assign;

	to_assign.add(5);
	to_assign.add(4);
	to_assign.add(2);
	to_assign.add(7);
	std::cout << "instantiation of a tree to_assign" << std::endl << to_assign;

	tree = to_assign;

	std::cout << "test the assignement of to_assign to the previous tree" << std::endl << "print of the assigned tree" << tree;

	

	//test deletion

	bstree<int, compare_int_e, compare_int_l> deletion_tree;

	deletion_tree.add(10);
	deletion_tree.add(3);
	deletion_tree.add(6);
	deletion_tree.add(11);
	deletion_tree.add(12);
	deletion_tree.add(2);
	deletion_tree.add(13);
	deletion_tree.add(50);
	deletion_tree.add(4);
	deletion_tree.add(5);

	std::cout << "print of new tree deletion_tree " << std::endl << deletion_tree;

	std::cout << "test of delete_node" << std::endl;

	deletion_tree.delete_node(3);

	std::cout << "after deletion of (3) from deletion_tree " << std::endl << deletion_tree;

	deletion_tree.delete_node(10);

	std::cout << "after deletion of (10) from deletion_tree " << std::endl << deletion_tree;

	deletion_tree.delete_node(5);

	std::cout << "after deletion of (5) from deletion_tree " << std::endl << deletion_tree;

	//test of clear bstree
	deletion_tree.clear();

	std::cout << "after clear of deletion_tree" << std::endl << deletion_tree;

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
	std::cout << "(9) is leaf? " << subtree_test.is_leaf(16) << std::endl;
	std::cout << "(10) is leaf? " << subtree_test.is_leaf(10) << std::endl;

	//test of is_in_subtree
	std::cout << "(10) is in subtree with root (12)? " << subtree_test.is_in_subtree(12, 10) << std::endl;
	std::cout << "(13) is in subtree with root (12)? " << subtree_test.is_in_subtree(12, 13) << std::endl;



}


//Test con T stringa
void test_2(){
	std::cout << "********** Start of test_2 with type STRING **********" << std::endl;

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

	copy_string_tree.add("mickey mouse");

	std::cout << "print of copy_string_tree after add of element" << std::endl << copy_string_tree << std::endl;

	std::cout << "mickey mouse is leaf? " << copy_string_tree.is_leaf("mickey mouse") << std::endl;

	bstree<std::string, compare_string_e, compare_string_l>::const_iterator i, ie;

	i = copy_string_tree.begin();
	ie = copy_string_tree.end();

	while(i != ie){
		std::cout << ("iteration") << std::endl;
		++i;
	}

	std::cout << "print of copy_string_tree after add of element" << std::endl << copy_string_tree << std::endl;

	i = copy_string_tree.begin();
	ie = copy_string_tree.end();

	bstree<std::string, compare_string_e, compare_string_l>::const_iterator copy_i(i);

	std::cout << "instantiation of a new iterator by copy " << std::endl << "test of the copied iterator " << std::endl;

	while(copy_i != ie){
		std::cout << "iteration: " << *copy_i << std::endl;
		++copy_i;
	}

	i = copy_string_tree.begin();
	ie = copy_string_tree.end();

	copy_i = ie;

	std::cout << "assignement of ie to copy_i " << std::endl << "test of the assigned iterator " << std::endl;

	while(i != copy_i){
		std::cout << "iteration: " << *i << std::endl;
		++i;
	}

}

//Test con T struct
void test_3(){
	std::cout << "********** Start of test_3 with custom type TEST_STRUCT **********" << std::endl;
	bstree<test_struct, compare_struct_e, compare_struct_l> struct_tree;

	test_struct s(5, 'a', 0.1);

	std::cout << "add of test_struct s(5, 'a', 0.1) to struct_tree" << std::endl;

	struct_tree.add(s);
	
	std::cout << "print of struct_tree " << std::endl << struct_tree << std::endl;

	std::cout << "check of s" << std::endl << struct_tree.check(s) << std::endl;

	struct_tree.delete_node(s);

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

	return 0;
}