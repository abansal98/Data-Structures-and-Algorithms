#include <iostream>
#include <iomanip>
#include <iostream>

/*forward declaration*/
template <class T>
class Queue;

template <class T>
class BST{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data,Node* lt=nullptr,Node* rt=nullptr){
			data_=data;
			left_=lt;
			right_=rt;
		}
	};
	Node* root_;

	void printPreOrder(Node* subroot)const{
		if(subroot){
			std::cout << subroot->data_ << " ";		
			printPreOrder(subroot->left_);
			printPreOrder(subroot->right_);
		}
	}
	void printInOrder(Node* subroot)const{
		if(subroot){
			printInOrder(subroot->left_);
			std::cout << subroot->data_ << " ";
			printInOrder(subroot->right_);
		}
	}
	void destroy(Node* subroot){
		if(subroot){
			destroy(subroot->left_);
			destroy(subroot->right_);
			delete subroot;
		}
	}
	
	bool isSame(const Node* left, const Node* right) const;

	/*used by print() to print all nodes at same level*/
	void printLine(Node* data[],int numNodes,int width) const{
		int half=width/2;
		int firsthalf=width%2?half+1:half;

		if(numNodes > 1){
			for(int i=0;i<numNodes;i++){
				if(i%2==0){
					if(data[i]){
						std::cout << std::right <<std::setfill(' ') << std::setw(firsthalf)<< "-";
						std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
					}
					else{
						std::cout << std::right <<std::setfill(' ') << std::setw(firsthalf)<< " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
				else{
					if(data[i]){
						std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
						std::cout << std::left <<std::setfill(' ') << std::setw(half)<<"-";
					}
					else{
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
					}
				}
			}
			std::cout << std::endl;
		}
		for(int i=0;i<numNodes;i++){
			if(data[i]){
				if(i%2==0){
					std::cout << std::right << std::setw(firsthalf) << "|";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
				}
				else{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<< "|";				
				}
			}
			else{
				std::cout << std::left <<std::setfill(' ') << std::setw(width)<<" ";			
			}
		}
		std::cout << std::endl;		
		for(int i=0;i<numNodes;i++){
			if(data[i]){
				if(i%2==0){
					std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
				}
				else{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<< data[i]->data_;				
				}
			}
			else{
				std::cout << std::left <<std::setfill(' ') << std::setw(width)<<" ";			
			}
		}
		std::cout << std::endl;

	}

	Node* remove(const T& data, Node* subroot){
		if(subroot){
			if(subroot->data_ == data){
				if(subroot->left_ != nullptr && subroot->right_ != nullptr){
					Node* temp = subroot;
					subroot = detachSmaller(subroot->right_);
					subroot->right_ = temp->right_;
					subroot->left_ = temp->left_;
					delete temp;
				}
				else if(subroot->left_){
					Node* temp = subroot;
					subroot = subroot->left_;
					delete temp;
				}
				else if(subroot->right_){
					Node* temp = subroot;
					subroot = subroot->right_;
					delete temp;
				}
				else {
					delete subroot;
					subroot = nullptr;
				}
			}
			else{
				if(data < subroot->data_ ){
					if(subroot->left_){
						subroot->left_ = remove(data, subroot->left_);
					}
				}
				else{
					if(subroot->right_){
						subroot->right_ = remove(data, subroot->right_);
					}
				}
			}
		}
		return subroot;
	}

	Node* detachSmaller(Node*& subroot){
		Node* nn = nullptr;
		if(subroot->left_){
			nn = detachSmaller(subroot->left_);
		}
		else{
			nn = subroot;
			if(subroot->right_){
				subroot = subroot->right_;
			}
			else
				subroot = nullptr;
		}
		return nn; 
	}

	
	Node* treeCreation(T& data, Node* root){
		Node* nn = new Node(data, nullptr, nullptr);
		if(root){
			if(root->left_){
				nn->left_ = treeCreation(root->left_->data_, root->left_);
			}
			if(root->right_){
				nn->right_ = treeCreation(root->right_->data_, root->right_);
			}
		}
		else{
			return nullptr;
		}
		return nn;	
	}


public:
	BST(){
		root_=nullptr;
	}

	BST(const BST& rhs){
		root_ = treeCreation(rhs.root_->data_, rhs.root_);
	}

	void remove(const T& data){
		root_ = remove(data, root_);
	}

	int depth(const T& data){
		return getDepth(root_, data);
	}

	int getDepth(Node* root, const T& data, int depth = 0){
		int rc = -1;
		if(root){
			if(root->data_ == data){
				rc = depth;
			}
			if(data < root->data_){
				if(root->left_ && rc == -1){
					rc = getDepth(root->left_, data, depth+1);
				}
			}
			else{
				if(root->right_ && rc == -1){
					rc = getDepth(root->right_, data, depth+1);
				}
			}
		}
		return rc;
	}


	void printPreOrder() const{
		printPreOrder(root_);
		std::cout << std::endl;
	}
	void printInOrder() const{
		printInOrder(root_);
		std::cout << std::endl;
	}


	void insert(const T& data){
		if(root_==nullptr){
			root_=new Node(data);
		}
		else{

			Node* curr=root_;
			while(curr != nullptr){
				if(data < curr->data_){
					//go left
					if(curr->left_){
						curr=curr->left_;
					}
					else{
						curr->left_=new Node(data);
						curr=nullptr;
					}
				}	
				else{
					//go right
					if(curr->right_){
						curr=curr->right_;
					}
					else{
						curr->right_=new Node(data);
						curr=nullptr;
					}
				}
			}

		}

	}

	bool operator==(const BST& rhs) const;
	void print() const{
		struct Output{
			Node* node_;
			int lvl_;
			int position_;
			Output(Node* n=nullptr,int l=0, int p=0){
				node_=n;
				lvl_=l;
				position_=p;
			}
			void set(Node* n=nullptr,int l=0, int p=0){
				node_=n;
				lvl_=l;
				position_=p;
			}
		};
		Queue<Output> theNodes;
		Node* line[16];
		if(root_){
			for(int i=0;i<16;i++){
				line[i]=nullptr;
			}
			theNodes.enqueue(Output(root_,0,0));
			int currline=0;
			int width=80;
			int numInLine=1;
			while(theNodes.isEmpty()==false){
				Output curr=theNodes.front();
				if(curr.node_->left_)
					theNodes.enqueue(Output(curr.node_->left_,curr.lvl_+1,curr.position_*2));
				if(curr.node_->right_)
					theNodes.enqueue(Output(curr.node_->right_,curr.lvl_+1,curr.position_*2+1));
				theNodes.dequeue();


				if(curr.lvl_>currline){
					printLine(line,numInLine,width);
					width=width/2;
					numInLine=numInLine*2;
					for(int i=0;i<16;i++){
						line[i]=nullptr;
					}
					currline++;

				}
				line[curr.position_]=curr.node_;
			}
			printLine(line,numInLine,width);
			std::cout << std::endl;

		}
		else{
			std::cout << "tree is empty" << std::endl;
		}
	}
	~BST(){
		destroy(root_);
	}
};

template <class T>
class Queue{
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;
	int back_;
	void grow(){
		T* tmp=new T[capacity_*2];
		int j;
		for(int i=0,j=front_;i<used_;i++,j=(j+1)%capacity_){
			tmp[i]=theQueue_[j];
		}
		delete [] theQueue_;
		theQueue_=tmp;
		capacity_=capacity_*2;
		front_=0;
		back_=used_;
	}
public:
	Queue(){
		theQueue_=new T[50];
		capacity_=50;
		used_=0;
		front_=0;
		back_=0;
	}
	void enqueue(const T& data){
		if(used_==capacity_){
			grow();
		}
		theQueue_[back_]=data;
		back_=(back_+1)%capacity_;
		used_++;
	}
	void dequeue(){
		if(!isEmpty()){
			used_--;
			front_=(front_+1)%capacity_;
		}
	}
	T front() const{
		if(!isEmpty()){
			return theQueue_[front_];
		}
		return T{};

	}
	bool isEmpty() const{
		return used_==0;
	}
	~Queue(){
		delete [] theQueue_;
	}	
};
