#include <iostream>
using namespace std;

template <class T>
class ThreadedTree {
	struct Node {
		Node* left_;
		Node* right_;
		bool lthread_;
		bool rthread_;
		T data_;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr, bool lthread = false, bool rthread = false) {
			data_ = data;
			left_ = left;
			right_ = right;
			lthread_ = lthread;
			rthread_ = rthread;
		}
	};
	Node* root_;
	Node* smallest_;		//pointer to the node with the smallest data in the tree
	Node* largest_;			//pointer to the node with the largest data in the tree
	
	void print(const Node* rt, int lvl)const {
		//This function won't be tested, but you may find it useful to implement this so 
		//that you can see what the tree looks like.  lvl will allow you to use dashes to 
		//better show shape of tree
	}

public:
	class const_iterator {
	protected:

		Node* curr_;
		const ThreadedTree* tree_;

		//constructor for the const_iterator
		//takes two arguments, a pointer to a Node and a pointer to a ThreadedTree
		const_iterator(Node* curr, const ThreadedTree* tree) { 
			curr_ = curr;
			tree_ = tree;
		}

	public:
		const_iterator() {
			curr_ = nullptr;
		}

		//prefix ++ operator for const_iterators
		//returns an iterator to the node with the next larger value than the data in the current
		const_iterator operator++() {
			if (this->curr_->right_) {
				if (this->curr_->rthread_) {
					this->curr_ = this->curr_->right_;
				}
				else {
					this->curr_ = this->curr_->right_;				//going to the right subtree of the current node

					while (this->curr_->lthread_ == false) {		//finding the smallest node in the current subtree
						this->curr_ = this->curr_->left_;
					}
				}
			}
			else
				this->curr_ = nullptr;

			return *this;
		}

		//postfix ++ operator for const_iterators
		//Uses the prefix ++ operator
		//sets the curr pointer to point to the next larger node
		//returns an iterator to the node before the change
		const_iterator operator++(int) {
			const_iterator temp = *this;
			++(*this);

			return temp;
		}

		//prefix -- operator for const_iterators
		//returns an iterator to the node with the next smaller value than the data in the current
		const_iterator operator--() {
			if (this->curr_ == nullptr) {
				this->curr_ = this->tree_->largest_;
				return *this;
			}

			if (this->curr_->left_) {
				if (this->curr_->lthread_) {
					this->curr_ = this->curr_->left_;
				}
				else {
					this->curr_ = this->curr_->left_;				//going to the left subtree of the current node

					while (this->curr_->rthread_ == false) {		//finding the largest node in the current subtree
						this->curr_ = this->curr_->right_;
					}
				}
			}

			return *this;
		}

		//postfix -- operator for const_iterators
		//Uses the prefix -- operator
		//sets the curr pointer to point to the next smaller node
		//returns an iterator to the node before the change
		const_iterator operator--(int) {
			const_iterator temp = *this;
			--(*this);
			return temp;
		}

		//Dereference operator
		//returns the data stored in the current node
		const T& operator*() const {
			return this->curr_->data_;
		}

		//== operator fir const_iterator
		//takes a const_iterator as the argument
		//return true if the curr_ pointer of the passed const_iterator points to the same node as "this->curr_"
		//return false otherwise
		bool operator==(const const_iterator& rhs) const {
			return curr_ == rhs.curr_;
		}

		//!= operator for const_iterator
		//takes a const_iterator as the argument
		//return true if the curr_ pointer of the passed const_iterator do not point to the same node as "this->curr_"
		//return false otherwise
		bool operator!=(const const_iterator& rhs) const {
			return curr_ != rhs.curr_;
		}

		friend class ThreadedTree;
	};

	class iterator :public const_iterator {

		//construtor for iterator uses the constructor for the const_iterator
		iterator(Node* curr, const ThreadedTree* tree) :const_iterator(curr, tree) {}

	public:
		iterator() :const_iterator() {}

		//dereference operator
		//returns the data stored in the current node
		const T& operator*() const {
			return this->curr_->data_;
		}

		//Dereference operator
		//returns the data stored in the current node
		T& operator*() {
			return this->curr_->data_;
		}

		//prefix ++ operator for iterator
		//uses the prefix ++ operator for const_iterator
		iterator operator++() {
			const_iterator::operator++();
			return *this;
		}

		//postfix ++ operator for iterator
		//uses the postfix ++ operator for const_iterator
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}

		//prefix -- operator for iterator
		//uses the prefix -- operator for const_iterator
		iterator operator--() {
			const_iterator::operator--();
			return *this;
		}

		//postfix -- operator for iterator
		//uses the postfix -- operator for const_iterator
		iterator operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}

		friend class ThreadedTree;

	};


private:

	//a recursive function for adding new nodes to the tree
	//takes 2 arguments, one of the type T, and a pointer to node
	//returns a pointer to the node passed in the argument to the function
	Node* insertion(const T& data, Node* parent) {
		if (parent) {
			//adding a node to the left subtree of the tree
			if (data < parent->data_) {
				if (parent->left_ && parent->lthread_ == false) {
					insertion(data, parent->left_);
				}
				else if (parent->left_ && parent->lthread_) {
					parent->lthread_ = false;
					parent->left_ = new Node(data, parent->left_, parent, true, true);
					if (data < smallest_->data_) {
						smallest_ = parent->left_;
					}
				}
				else {
					parent->left_ = new Node(data, nullptr, parent, false, true);
					if (data < smallest_->data_) {
						smallest_ = parent->left_;
					}
				}
			}
			//adding a node to the right subtree of the tree
			else {
				if (parent->right_ && parent->rthread_ == false) {
					insertion(data, parent->right_);
				}
				else if (parent->right_ && parent->rthread_) {
					parent->rthread_ = false;
					parent->right_ = new Node(data, parent, parent->right_, true, true);
					if (data > largest_->data_) {
						largest_ = parent->right_;
					}
				}
				else {
					parent->right_ = new Node(data, parent, nullptr, true, false);
					if (data > largest_->data_) {
						largest_ = parent->right_;
					}
				}
			}
		}
		//this else statement is executed when the current tree is empty
		else {
			parent = new Node(data);
		}

		return parent;
	}

	//search function
	//takes two arguments, one is 'data' of the type T, and root which is the pointer to the root node of a tree 
	//finds the node in the tree containing the data
	//returns a pointer to the node containing the data
	Node* search(const T& data, Node* root){
		Node* curr;

		if (root_) {
			curr = root_;
			bool done = false;

			while (!done) {
				if (data == curr->data_) {
					done = true;
					return curr;
				}
				else if (data < curr->data_ && curr->left_) {
					curr = curr->left_;
				}
				else if (data > curr->data_ && curr->right_) {
					curr = curr->right_;
				}
				else {
					done = true;
				}
			}
		}

		return nullptr;
	}

public:
	ThreadedTree() {
		root_ = nullptr;
	}

	//insert function for the ThreadedTree
	//takes one argument of the type T
	//calls the insertion function
	void insert(const T& data) {
		if (root_ == nullptr) {
			root_ = insertion(data, root_);
			smallest_ = root_;
			largest_ = root_;
		}
		else
			root_ = insertion(data, root_);
	}

	//find function for the ThreadedTree
	//takes one argument of the type T, to tell the function what node to look for
	//calls the search function to find the node
	//returns an iterator to the node containing the data
	iterator find(const T& data) {
		Node* foundNode = search(data, root_);

		if(foundNode)
			return iterator(foundNode, this);
		else
			return iterator();
	}

	//find function for the ThreadedTree
	//takes one argument of the type T, to tell the function what node to look for
	//calls the search function to find the node
	//returns a const_iterator to the node containing the data
	const_iterator find(const T& data) const {
		Node* foundNode = search(data, root_);

		if(foundNode)
			return const_iterator(foundNode, this);
		else
			return const_iterator();
	}

	//returns a const_iterator to the node in the tree with the smallest data
	const_iterator cbegin()const {
		if(root_)
			return const_iterator(smallest_, this);
		else
			return const_iterator();
	}

	//returns a const_iterator to the node in the tree with the largest data
	const_iterator cend() const {
		if(root_)
			return const_iterator(largest_->right_, this);
		else
			return const_iterator();
	}

	//returns a iterator to the node in the tree with the smallest data
	iterator begin() {
		if(root_)
			return iterator(smallest_, this);
		else
			return iterator();
	}

	//returns a iterator to the node in the tree with the largest data
	iterator end() {
		if(root_)
			return iterator(largest_->right_, this);
		else
			return iterator();
	}

	void print() const {
		//this function won't be tested, but you may wish to implement this 
		//to help you debug
	}

	//destructor for the ThreadedTree
	~ThreadedTree() {
		iterator it;
		Node* temp;

		if(root_){
			it = begin();

			while(it.curr_){
				temp = it.curr_;
				it++;
				delete temp;
			}
		}
		
		root_ = nullptr;
		smallest_ = nullptr;
		largest_ = nullptr;
	}
};