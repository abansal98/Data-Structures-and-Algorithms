template <typename T>

class RecentList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{}, Node* nx = nullptr, Node* pr = nullptr){
			data_ = data;
			next_ = nx;
			prev_ = pr;
		}
	};
	Node* front_;	//pointer to the first node in the list. In this case it is a sentinel node.
	Node* back_;	//pointer to the last node in the list. In this case it is a sentinel node.
	int size_ = 0;	//size of the list. Number of nodes in the list excluding the sentinel nodes.

	//this function creates a new empty list
	//creates 2 sentinel nodes and links them together
	//sets the size of the list to 0
	void init(){
		front_ = new Node();
		back_  = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
		size_ = 0;
	}

public:
	class const_iterator{
		/*declaring RecentList as a friend class to allow access to all the data members of
		**the RecentList class
		*/
		friend class RecentList<T>;

	protected:
		const RecentList* recentList_;	//pointer to the current list
		Node* curr_;			//pointer to the current node in the list

		//takes 2 parameters of the type Node* and RecentList*
		//changes the curr_ pointer to point to the Node* passed to the function
		//changes the recentList_ pointer to the RecentList* passed to the function
		const_iterator(Node* curr, const RecentList* list){
			curr_ = curr;
			recentList_ = list;
		}

	public:

		const_iterator(){}

		//Const prefix ++ operator
		//modifies the current node pointer so that it points to the next node in the list
		//returns the modified iterator pointing to the next node in the list
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}

		//Const postfix ++ operator
		//modifies the current node pointer so that it points to the next node in the list
		//returns a new const_iterator pointing to the node before the modification
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;	//call the prefix ++ operator
			return old;
		}

		//Const prefix -- operator
		//modifies the current node pointer so that it points to the previous node in the list if it exists
		//return the modified iterator pointing to the previous node in the list
		const_iterator operator--(){
			if(curr_){
				curr_ = curr_->prev_;
			}
			else{
				if(recentList_){
					curr_ = recentList_->back_->prev_;
				}
			}
			return *this;
		}

		//const postfix -- operator
		//modifies the current node pointer to point to the previous node in the list
		//returns a new const_iterator pointing to the node before the modification	
		const_iterator operator--(int){
			const_iterator old = *this;
			--(*this);	//call the prefix -- operator
			return old;
		}

		//operator == 
		//takes 1 parameter of the type const_iterator
		/*return true if the the passed iterator points to the same RecentList and
		**the curr_ node pointers also point to the same node in the list
		*/
		//return false otherwise
		bool operator==(const_iterator rhs){
			return (recentList_ == rhs.recentList_) && (curr_ == rhs.curr_);
		}

		//A not(!) operator of the opeartor== above
		//returns true when operator== returns false
		//returns false when operator== returns true
		bool operator!=(const_iterator rhs){
			return (!(*this == rhs));
		}
		
		//returns a const reference to the data contained in the node to which the iterator refers to
		const T& operator*()const{ return curr_->data_; }
	};

	class iterator:public const_iterator{
		friend class RecentList<T>;

	protected:
		//iterator constructor
		//inherited from the const_iterator class
		iterator(Node* curr, RecentList* recentList):const_iterator(curr, recentList){}
		
	public:
		iterator(){}
		
		//similar to the const_iterator prefix ++ opeartor
		//returns a modiofiable iterator
		iterator operator++(){
			const_iterator::operator++();
			return *this;
		}

		//similar to the const_iterator postfix ++ operator
		//returns a modifiable iterator
		iterator operator++(int){
			iterator old = *this;
			++(*this);
			return old;
		}

		//similar to the const_iterator prefix -- operator
		//returns a modifiable iterator
		iterator operator--(){
			const_iterator::operator--();
			return *this;
		}
		
		//similar to the const iterator postfix -- operator
		//returns a modifiable iterator
		iterator operator--(int){
			iterator old = *this;
			--(*this);
			return old;
		}
		
		//returns a reference to the data in the node to which the iterator refers to
		T& operator*(){ return this->curr_->data_; }
		
		//returns a const reference to the data in the node to which the iterator refers to
		const T& operator*()const{ return this->curr_->data_; }
	};

	RecentList();
	~RecentList();
	RecentList(const RecentList& rhs);
	RecentList& operator=(const RecentList& rhs);
	RecentList(RecentList&& rhs);
	RecentList& operator=(RecentList&& rhs);
	
	//returns an iterator to the first node in the list with data
	iterator begin(){
		return iterator(front_->next_, this);	//calls the iterator constructor
	}

	//returns an iterator to the node after the last node with data in the list
	iterator end(){
		return iterator(back_, this);	//calls the iterator constructor
	}

	//returns a const iterator to the first node in the list with data
	const_iterator cbegin() const {
		return const_iterator(front_->next_, this);	//calls the const_iterator constructor
	}
	
	//returns a const iterator to the node after the last node with data in the list
	const_iterator cend() const {
		return const_iterator(back_, this);	//calls the const_iterator constructor
	}

	void insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};


//default constructor of the RecentList class
template <typename T>
RecentList<T>::RecentList(){
	init(); //creates a new empty list
}

//destructor of the RecentList class
template <typename T>
RecentList<T>::~RecentList(){
	Node* curr = front_;
	while(curr){
		Node* temp = curr;
		curr = curr->next_;
		delete temp;
	}
}

//copy constructor
template <typename T>
RecentList<T>::RecentList(const RecentList& rhs){
	*this = rhs;
}

//assignment operator
//checks if the list refered to by the rhs is not empty and is not the same list as the current list
/*initializes a new empty list and iteratively adds new nodes to the current list with the data from
**the list passed to the function
*/ 
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs){
	init();		//initializes a new empty list
	if(!rhs.empty()){	
		if(this != &rhs){
			for(const_iterator it = rhs.cbegin(); it != rhs.cend(); it++){ //iterates starting from the beginning of the list until the end
				this->insert(*it);	//inserts new node to the list with data
			}
		}
	}
	return *this;
}

//move constructor
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs){
	*this = rhs;	//uses move operator for this process
}

//move opearator
//calls the assignment operator to assign the parameter object to the current object
//returns the current list
template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs){
	return *this = rhs;	
}

//takes the data of the type T(template) as a parameter
//inserts data to the back of the RecentList
//increases the size of the list by one
template <typename T>
void RecentList<T>::insert(const T& data){
	Node* nn = new Node(data, back_, back_->prev_);
	back_->prev_->next_ = nn;
	back_->prev_ = nn;
	size_++;
}

//search function to search if the data is present in the current list
//takes data as a parameter
//moves the node to the front of the list if the data is found
//returns an iterator to the beginning of the list if data is found
//returns an iterator to the end of the list if the data is not found in the list
template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data){
	iterator rc = end();
	for(iterator it = begin(); it != end(); it++){
		if(*it == data){
			Node* temp = it.curr_;
			temp->next_->prev_ = temp->prev_;
			temp->prev_->next_ = temp->next_;
			temp->next_ = front_->next_;
			temp->prev_ = front_;
			front_->next_->prev_ = temp;
			front_->next_ = temp;
			rc = begin();
		}
	}
	return rc;
}

//erase function to delete a node in the list to which the iterator refers to
//takes an iterator as a parameter
//deletes the related node nad adjusts the links between the nodes and also adjusts the size
//returns an iterator to the next node in the list after the node to be removed
template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it){
	if(size_ > 0){
		Node* temp = it.curr_;
		it++;
		if(temp->next_ && temp->prev_){
			temp->next_->prev_ = temp->prev_;
			temp->prev_->next_ = temp->next_;
			delete temp;
			size_--;
		}
	}
	return it;
}

//erase function overload to delete multiple nodes
//takes 2 parameters of the type iterator
/*deletes all the nodes between the first iterator and the second iterator
**except the node refered to by the last iterator
*/
template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last){
	do{
		first = erase(first);
	}
	while(first != last);
}

//function to check if the current list is an empty list
//return true if the sentinel nodes point to each other using the next_ and prev_ properties
//returns false otherwise
template <typename T>
bool RecentList<T>::empty() const{
	return ((front_->next_ == back_) && (back_->prev_ == front_));
}

//function to get the size of the current list
//returns the int value of the data member size_ for the current list
template <typename T>
int RecentList<T>::size() const{
	return size_;
}
