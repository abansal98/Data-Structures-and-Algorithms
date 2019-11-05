/*************************************************************/
/*                                                           */
/*    starter file for a2                                    */
/*    v 1.1: removed SimpleTable::grow() function def.       */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <iostream>
#include <functional>
using namespace std;

template <class TYPE>
class Table{
public:
	Table(){}
	virtual bool update(const string& key, const TYPE& value)=0;
	virtual bool remove(const string& key)=0;
	virtual bool find(const string& key, TYPE& value)=0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

	struct Record{
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data){
			key_=key;
			data_=data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);

public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const{return size_==0;}
	virtual int numRecords() const{return size_;}
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key){
	int rc=-1;
	for(int i=0;i<size_;i++){
		if(records_[i]->key_==key){
			rc=i;
		}
	}
	return rc;
}


template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
	records_=new Record*[capacity];
	max_=capacity;
	size_=0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records_=new Record*[other.max_];
	max_=other.max_;
	size_=0;
	for(int i=0;i<other.size_;i++){
		update(other.records_[i]->key_,other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	size_=other.size_;
	max_=other.max_;
	records_=other.records_;
	other.records_=nullptr;
	other.size_=0;
	other.max_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx=search(key);
	if(idx==-1){
		if(size_ < max_){
			records_[size_++]=new Record(key,value);
			for(int i=0;i<size_-1;i++){
				for(int j=0;j<size_-1-i;j++){
					if(records_[j] > records_[j+1]){
						TYPE tmp=records_[j];
						records_[j]=records_[j+1];
						records_[j+1]=tmp;
					}
				}
			}
		}
	}
	else{
		records_[idx]->data_=value;
	}
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=search(key);
	if(idx!=-1){
		delete records_[idx];
		for(int i=idx;i<size_-1;i++){
			records_[i]=records_[i+1];
		}
		size_--;
		return true;
	}
	else{
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=search(key);
	if(idx==-1)
		return false;
	else{
		value=records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){
		if(records_){
			int sz=size_;
			for(int i=0;i<sz;i++){
				remove(records_[0]->key_);
			}
			delete [] records_;
		}
		records_=new Record*[other.max_];
		max_=other.max_;
		size_=0;
		for(int i=0;i<other.size_;i++){
			update(other.records_[i]->key_,other.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	swap(records_,other.records_);
	swap(size_,other.size_);
	swap(max_,other.max_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){
		int sz=size_;
		for(int i=0;i<sz;i++){
			remove(records_[0]->key_);
		}
		delete [] records_;
	}
}

template <class TYPE>
class LPTable:public Table<TYPE>{
	struct Record{
		TYPE data_;
		string key_;
		Record(const string &key, const TYPE &data){
			key_ = key;
			data_ = data;
		}
	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int capacity_;
	int search(const string& key);
	std::hash<std::string> hashFunction;
	
public:
	LPTable(int capacity, double maxLoadFactor);
	LPTable(const LPTable& other);
	LPTable(LPTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const LPTable& operator=(const LPTable& other);
	virtual const LPTable& operator=(LPTable&& other);
	virtual ~LPTable();
	virtual bool isEmpty() const { return size_ == 0; }
	virtual int numRecords() const { return size_; }

};

//search function takes a key of the type string as the only parameter.
//starts at the hash index of the key and loops through to find the record with the matching key
//returns the index of the record if found
//returns -1 otherwise
template <class TYPE>
int LPTable<TYPE>::search(const string& key) {
	size_t idx = hashFunction(key) % capacity_;		//hash index of the provided key
	int loopCounter = 0;

	while(records_[idx] != nullptr && loopCounter < capacity_){
		if(records_[idx]->key_ == key){
			return idx;
		}
		loopCounter++;
		idx = (idx + 1) % capacity_;
	}

	return idx;
}

//LPTable contructor takes 2 arguments, capacity if type integer and maxLoadFactor of type double
//intializes an instance of the LPTable with properties as below.
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity,double maxLoadFactor): Table<TYPE>() {
	capacity_ = capacity;
    max_ = capacity * maxLoadFactor;
    records_ = new Record*[capacity_];
	size_ = 0;

	for (int i = 0; i < capacity_; i++) {
		records_[i] = nullptr;
	}
}

//copy constructor
//takes one argument of the type LPTable
//uses assignment operator for this
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
	*this = other;
}

//move constructor
//takes one argument of the type LPTable
//uses ,ove assignment operator for this
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
	*this = other;
}

//update function
//takes 2 arguments key of type string and value of various types
//adds or updates an existing record in the table with the provided key value pair
//return true if a record was updated or added
//return false if the table is full and the key didn't exist in the table already
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key);

	if(size_ == max_){
		if(records_[idx] == nullptr){
			return false;
		}
		else{
			records_[idx]->data_ = value;
		}
	}
	if(records_[idx] == nullptr){
		records_[idx] = new Record(key, value);
		size_++;
	}

	return true;
}

//remove function
//takes one argument key of the type string
//removes the record that matches the provided key
//adjusts the records with a higher index accordingly
template <class TYPE>
bool LPTable<TYPE>::remove(const string& key) {
	int idx = search(key);
	int idxTemp = 0;
	int currElemLoc = 0;


	if(records_[idx] != nullptr){
		delete records_[idx];
		records_[idx] = nullptr;
		size_--;

		idxTemp = idx;
		currElemLoc = (idxTemp + 1) % capacity_;
		while(records_[currElemLoc] != nullptr){
			idxTemp = search(records_[currElemLoc]->key_);
			if(idxTemp != currElemLoc && idxTemp <= idx && idx < currElemLoc ||			//checks if the empty record is
				(idxTemp <= idx && currElemLoc < idxTemp) ||							//between the hash index and the 
				(idx < currElemLoc && currElemLoc < idxTemp)){							//current position of a record
				records_[idx] = new Record(records_[currElemLoc]->key_, records_[currElemLoc]->data_);		//move the record to an empty space
				delete records_[currElemLoc];
				records_[currElemLoc] = nullptr;
				size_--;
				idx = currElemLoc;
			}
			currElemLoc = (currElemLoc + 1) % capacity_;
		}
		return true;
	}
	else
		return false;

}

//find function
//takes a key of type string and a value reference as the two parameters
//uses the search function for searching for the provided key in the table
//return false if the the search function return index points to nullptr
//return true is key was found in the table. Sets the value to the data of record at the returned index
template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key);
	if(records_[idx] != nullptr){
		value = records_[idx]->data_;
		return true;
	}
	else
		return false;
}

//Assignment operator
//takes a const argument of the type LPTable
//initializes a new table with the data from the LPTable object passed to the function
//return the current object
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
	if(this!=&other){
		if(records_){
			delete [] records_;
		}
		capacity_ = other.capacity_;
		records_ = new Record*[capacity_];
		max_ = other.max_;
		size_=0;
		for(int i = 0; i < capacity_; i++){
		if(other.records_[i] != nullptr)
			update(other.records_[i]->key_,other.records_[i]->data_);
		}
	}

	return *this;
}

//Move operator
//takes an argument of the type LPTable
//sets the records_ pointer of the current object to the records_ pointer of the passed object
//sets the max_ and size_ properties according to the values of the passed object
//destroyes the propertoes of the passed object by setting them to zero and nullptr
//return the current object
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
	max_ = other.max_;
	capacity_ = other.capacity_;
	size_ = other.size_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.max_ = 0;
	other.size_ = 0;
	other.capacity_ = 0;
	return *this;
}

//destructor
template <class TYPE>
LPTable<TYPE>::~LPTable() {
	delete[] records_;
}
