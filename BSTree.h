#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <algorithm>
#include <iostream>


class non_existent_value : public std::runtime_error{
public:
	/**
		Secondary constructor with error message

		@param message error message
	*/
	non_existent_value(const char *message) : std::runtime_error(message){}
};

class duplicated_value : public std::runtime_error{
public:
	/**
		Secondary constructor with error message

		@param message error message
	*/
	duplicated_value(const char *message) : std::runtime_error(message){}
};


template <typename T, typename compequalsT, typename complessT>
class bstree{

	struct node{
		T value; ///< value of the node
		node *left; ///< pointer to the left child node of the node
		node *right; ///< pointer to the right child node of the node
		node *father;///< pointer to the node father or the node

		/**
			Constructor for node given its value
		
			@param v value of the node
		*/
		node(const T &v) : value(v), left(0), right(0), father(0){}

		/**
			Constructor for node given its value, its left child and right child
		
			@param v value of the node
			@param l left child
			@param r right child
		*/
		node(node *l, const T &v, node *r) : value(v), left(l), right(r), father(0){}
		/**
			Constructor for node given its value and left child
		
			@param v value of the node
			@param l left child
		*/
		node(node *l, const T &v) : value(v), left(l), right(0), father(0){}
		/**
			Constructor for node given its value and its righ child
		
			@param v value of the node
			@param r right child
		*/
		node(const T &v, node *r) : value(v), left(0), right(r), father(0){}
		/**
			Default constructor
		*/
		node() : left(0),right(0), father(0){}
		/**
			Destructor
		*/
		~node() {
			father = 0;
			delete left;
			delete right;
		}

		/**
			Copy constructor	
			@param other node to copy
		*/
		node(const node &other) : value(other.value), left(other.left), right(other.right) {}

		/**
			Assignement operator 	
			@param other node to copy
		*/
		node &operator=(const node &other) {
			if( this!=&other) {
				value = other.value;
				left = other.left;
				right = other.right;
			}
			return *this;
		}
	};


	node *_root;
	int _size;



	/**
		Auxiliary method which returns the pointer to the node with the given value

		@param val value to look for
		@return the pointer to the node if it exists, otherwise 0
	*/
	node *find_helper(const T val) const {
		node *curr = _root;
		compequalsT comp_e;
		complessT comp_l;

		while(curr != 0){
			if(comp_e(curr->value, val)){
				return curr;
			}else{
				// if the current visited node value is less than the given value
				if(comp_l(curr->value, val)){
					curr = curr->right;
				}else{
					curr = curr->left;
				}
			}
		}
		return 0;
	}

		/**
		Return the node successor
		@param n node
		@return the successor of n
	*/
	node *successor(node *n){
		if(n->right != 0){
			return min_value(n->right);
		}
		while(n->father != 0 && n == n->father->right){
			n = n->father;
		}
		return n->father;
	}


	/**
		Return the node with the minimum value in the subtree of the given node
		@param n node
		@return the node with minimum value
	*/
	node* min_value(node *n) const{
		while(n->left != 0){
			n = n->left;
		}
		return n;
	}

		/**
		Return the node with the maximum value in the subtree of the given node
		@param n node
		@return the node with maximum value
	*/
	node* max_value(node *n) const{
		while(n->right != 0){
			n = n->right;
		}
		return n;
	}

	public:
	
	/**
		Default constructor
	*/
	bstree() : _root(0), _size(0){}

	/**
		Destructor
	*/
	~bstree() {
		clear();
	}

	/**
		Method to empty the bstree
	*/
	void clear() {
		delete _root;
		_root = 0;
		_size = 0;
	}

	/**
		Copy constructor
		
		@param other tree to copy
	*/
	bstree(const bstree& other) : _root(0), _size(0){
		typename bstree<T, compequalsT, complessT>::const_iterator i, ie;
		i = other.begin(); 
		ie = other.end();
		try {
			while (i != ie) {
				add(*i);
				++i;
			}
		}
		catch(...) {
			 clear();
			throw;
		}
	}

	/**
		Assignement operator
		
		@param other tree to copy
		@return *this
	*/
	bstree& operator=(const bstree &other) {
		if (this!=&other) {
			bstree temp(other);
			std::swap(this->_root,temp._root);
			std::swap(this->_size,temp._size);			
		}
		
		return *this;

	}

	/**
		Checks if the given value is present in the tree

		@param value to check existence
		@return true or false whether the value exists or not.
	*/
	bool check(const T &val) const {
		node *n = find_helper(val);
		
		return (n != 0);
	}

	/**
		Add a new node with the given value

		@param val
		@throw duplicated_value
	*/
	void add(const T &val){
		if(_size == 0){
			//node new_node(val);
			_root = new node(val);
			_size = _size + 1;
		}else{
		
			if(find_helper(val) == 0){
				bool found = 0;
				complessT comp_l;
				node *curr = _root;

				while(found == 0){	
					// if the current visited node is less than the given node
					if(comp_l(curr->value, val)){
						if(curr->right == 0){
							curr->right = new node(val);
							curr->right->father = curr;
							_size = _size + 1;
							found = 1;
						}else{
							curr = curr->right;
						}
					}else{
						if(curr->left == 0){
							curr->left = new node(val);
							curr->left->father = curr;
							_size = _size + 1;
							found = 1;
						}
						curr = curr -> left;
					}				
				}
			}else{
				throw duplicated_value("Already existing value.");
			}
		}
	}

	/**
		Delete the node with the given value

		@param val
		@throw non_existent_value
	*/
	void delete_node(const T &val){
		if(check(val)){
			node *d = find_helper(val); 
			if(d->left == 0 && d->right == 0){
				if(d->father != 0 && d->father->left == d){
					d->father->left = 0;
				}else if(d->father != 0 && d->father->right == d){
					d->father->right = 0;
				}

				d->father = 0;
				delete d;
				std::cout << "deleted node: " << d << " value: " << d->value << std::endl;			
			}
			else if(d->left == 0 && d->right != 0){
				if(d->father == 0){
					d->right->father = 0;
					_root = d->right;
				}else if(d->father->left == d){
					d->father->left = d->right;
				}else{
					d->father->right = d->right;
				}

				if(d->right != 0){
					d->right->father = d->father;
				}

				d->right = 0;
				d->father = 0;
				delete d;			
			}
			else if(d->left != 0 && d->right == 0){
				if(d->father == 0){
					d->left->father = 0;
					_root = d->left;
				}else if(d->father->left == d){
					d->father->left = d->left;

				}else{
					d->father->right = d->left;
				}

				if(d->left != 0){
					d->left->father = d->father;
				}

				d->left = 0;
				d->father = 0;
				delete d;
				std::cout << "deleted node: " << d << " value: " << d->value << std::endl;			
			}
			else{

				node* succ = successor(d);

				d->value = succ->value;

				if(succ->father->left == succ){
					succ->father->left = succ->right;
					if(succ->right != 0){
						succ->right->father = succ->father;
					}

				}else{

					succ->father->right = succ->right;
					std::cout << "qui entro " << std::endl;
					if(succ->right != 0){
						succ->right->father = succ->father;
					}
				}
				succ->left = 0;
				succ->right = 0;
				succ->father = 0;
				delete succ;
				std::cout << "deleted node: " << succ << " value: " << succ->value << std::endl;
			}
		}else{
			throw non_existent_value("The value inserted is not valid because it doesn't exist");
		}
		
	}

	/**
		Check if the node with the given value is a node leaf, that is a node with no children

		@param val
		@throw non_existent_value
	*/
	bool is_leaf(const T &val) const{
		node *temp = find_helper(val);
		if(temp != 0){
			if(temp->right == 0 && temp->left == 0){
				return 1;
			}
			return 0;
		}else{
			throw non_existent_value("The value inserted is not valid because it doesn't exist");
		}
	}

	/**
		Check if the node with the given value is part of the subtree with root the given subroot

		@param subroot_value
		@param val
		@throw non_existent_value
	*/
	bool is_in_subtree(const T &subroot_value, const T &val) const{
		complessT comp_l;
		compequalsT comp_e;
		node *subroot = find_helper(subroot_value);
		if(subroot == 0){
			throw non_existent_value("The value inserted is not valid because it doesn't exist");
		}
		node * min = min_value(subroot);
		node * max = max_value(subroot);
		T min_val = min->value;
		std::cout << "min: " << min_val << std::endl;
		T max_val = max->value;
		std::cout << "max: " << max_val << std::endl;
			if((!comp_l(val, subroot_value) && !comp_e(val, subroot_value)) && (comp_l(val, max_val) || comp_e(val, max_val))){
				return 1;
			}else if(comp_l(val, subroot_value) &&  (!comp_l(val, min_val) || comp_e(val, min_val))){
				return 1;
			}else{
				return 0;
			}
	}


	/**
		Return the number of nodes of the tree
		@return the number of nodes od the tree
	*/
	int get_size()  const {
		return _size;
	}


	/**
	 * Forward iterator read only
	 */
	class const_iterator{

		friend class bstree;

		const node *n;///<Pointer to the current node of the tree

		

		/**
			Secondary constructor
			@param pn pointer to a node of the tree
		*/
		const_iterator(const node *pn){
			n = pn;
		}

	public:
		typedef std::forward_iterator_tag iterator_category;
		/**
			Default constructor
		*/
		const_iterator(){
			n = 0;
		}

		/**
			Copy constructor
		*/
		const_iterator(const const_iterator &other){
			n = other.n;
		}

		/**
			Assignement operator
			@param other iterator to copy
			@return *this
		 */
		const_iterator &operator=(const const_iterator &other){
			n = other.n;
			return *this;
		}

		/** 
			Destructor
		*/
		~const_iterator(){}

		/**
		Dereference through reference
		@return constant reference to node
		*/
		const T& operator*() const{
			return n->value;
		}

		/**
		Dereference through pointer
		@return constant pointer to node
		*/
		/*const T* operator->() const{
			return &(n->value);
		}*/

		/**Post-increment
		@return the iterator to the previous node
		*/
		const_iterator operator++(int){
			const_iterator tmp(*this);

			if(n->left != 0){
				n = n->left;
				return tmp;
			}

			if(n->right != 0){
				n = n->right;
				return tmp;
			}
			while(n->father != 0){		
				if(n->father->right != 0 && n->father->right != n){
					n = n->father->right;
					return tmp;
				}
				n = n->father;
			}
			n = 0;
			return tmp;
		}

		/**Pre-increment
		@return the iterator to the following node
		*/
		const_iterator& operator++(){
			if(n->left != 0){
				n = n->left;
				return *this;
			}

			if(n->right != 0){
				n = n->right;
				return *this;
			}
			while(n->father != 0){		
				if(n->father->right != 0 && n->father->right != n){
					n = n->father->right;
					return *this;
				}
				n = n->father;
			}
			n = 0;
			return *this;
		}

		/**
			Compare (equals)
			@other iterator to compare
			@return true if both pointers point to the same position
		 */
		bool operator==(const const_iterator &other) const{
			return n == other.n;
		}

		/**
			Compare (not equals)
			@other iterator to compare
			@return false if both pointers point to the same position
		*/
		bool operator!=(const const_iterator &other) const{
			return n != other.n;
		}
	};//end class const_iterator

	/**
	 * Iterator of begin tree
	 * @return the iterator of begin tree
	 */
	 const_iterator begin() const{
	 	return const_iterator(_root);
	 }

	 /**
	 * Iterator of end tree
	 * @return the iterator at the end of the tree
	 */
	 const_iterator end() const{
	 	return const_iterator(0);
	 }

	 

};//end class bstree


/**
	Extract the subtree from the given tree from the node with the given value

	@param t the tree to extract from
	@param val the starting value
	@return the extracted subtree
	@throw non_existent_value
*/
template <typename T, typename compequalsT, typename complessT>
bstree<T,compequalsT, complessT> subtree(const bstree<T,compequalsT, complessT> &t,const T &val){

		if(t.check(val)){
			bstree<T,compequalsT, complessT> sub;		
			typename bstree<T, compequalsT, complessT>::const_iterator i, ie;

			i = t.begin();
			ie = t.end();

			while(*i != val){
				++i;
			}

 			const T subroot_value = *i;
 			sub.add(subroot_value);

 			if(!t.is_leaf(subroot_value)){
	 			++i;

	 			bool exit = 0;
				do{
					if(t.is_in_subtree(subroot_value, *i)){
						sub.add(*i);
						++i;
					}else{
						exit = 1;
					}
				}while(i != ie && !exit);
			}
			return sub;

		}else{
			throw non_existent_value("The value inserted is not valid because it doesn't exist");
		}

	}



/**
	Output stream operator to print a bstree
	@param os output stream
	@param tree bstree to print
	@return the output stream
*/
template <typename T, typename compequalsT, typename complessT>
std::ostream& operator<<(std::ostream &os, const bstree<T,compequalsT, complessT> &tree) {
		typename bstree<T, compequalsT, complessT>::const_iterator i, ie;

		if(tree.get_size() == 0){
			os << "Empty Tree" << std::endl;
			return os;
		}

		for(i = tree.begin(), ie = tree.end() ; i != ie; ++i){
			os << *i << std::endl;
		}

		return os;
	}


#endif