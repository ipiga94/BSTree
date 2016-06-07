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

void test_1(){

	bstree<int, compare_int_e, compare_int_l> tree;
	//bstree<int, compare_int_e, compare_int_l>::node nodo; 
	//nodo = bstree<int, compare_int_e, compare_int_l>::node(5);
	 
	//node node_2;
	//node node_3;

	/*node_1 = new bstree::node(3);
	node_2 = new bstree::node(node_1, 2);
	node_3 = new bstree::node(node_1, 1, node_2);*/

	//std::cout << "node_3.value: " << nodo.value << " node_3.left: " << nodo.left << " node_3.right: " << nodo.right << std::endl; 
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

	/*const bstree<int, compare_int_e, compare_int_l>::node *n; 
	n = another_tree.find_helper(13);

	std::cout << "successore: " << another_tree.succ(n);*/

	another_tree.delete_node(12);

	std::cout << "after deletion of (12)" << std::endl << another_tree;

	//test of clear bstree
	//delete &another_tree;

	std::cout << "after clear of another_tree" << std::endl << another_tree;

	//test of subtree
	bstree<int, compare_int_e, compare_int_l> sub = subtree(another_tree, 8); 
	std::cout << "stampo" << std::endl << sub << std::endl;

	//test of is_leaf
	std::cout << another_tree.is_leaf(9) << std::endl;
	std::cout << another_tree.is_leaf(10) << std::endl;


}


int main(){
    //test_1();
    test_2();

	return 0;
}