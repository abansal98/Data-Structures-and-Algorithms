#include <iostream>
#include <string>
#define MAX 10

class Stack{
	char stackArray_[MAX];
	int top_;
public:
	Stack(){
		top_ = 0;
	}
	void initialize(){
		Stack();
		stackArray_[MAX] = {'0'};
	}

	void push(char data){
		if(!isFull()){
			stackArray_[top_] = data;
			top_++;
		}
	}

	void pop(){
		if(!isEmpty()){
			top_--;
		}
	}
	
	int top() const{
		return stackArray_[top_ - 1];
	}
	
	bool isEmpty() const{
		return top_ == 0;
	}
	
	bool isFull() const{
		return top_ >= MAX;
	}
};
