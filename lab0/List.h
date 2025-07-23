#include "ListNode.h"
//no requirement for namespace here, will put in the .cpp file
// Jonathan Goohs
// Intermediate Programming and Data Strcutures Lab 0
#ifndef LIST_H
#define LIST_H

//Class template for Linked List Node

template<class T>
class List
{
public: //constructors
	//default
	List() : first(nullptr), last(nullptr), total(0) {}
	//defined constructor
	List(T& t) : first(new ListNode<T>(t, 0), last(nullptr), total(1)) {}
	~List();
	//destructor

	//insert method insert the value t into the position specified
	void insert(T& t, int position);
	//remove method will want to reference this and ensure we return an error code or not, and the t will be passed by reference
	int remove(T& t);
	//return the error code or not, but pass back the value of t by reference
	int count(T& t);  
	//return the error code or not, but pass back the value of t by reference
	void print(); //return list of all elements

protected:
	ListNode<T>* first;
	ListNode<T>* last;
	int total;
	//to instinatiate new list nodes via friendship relationship
	ListNode<T> *newNode(T& t, ListNode)

};

#endif

//can put the implementation here and then the .cpp file will have the main function with interactions from the user

List::insert(T& t, int position) {
	//if 
}

List::remove(T& t) {

}

List::count(T& t) {

}

List::print() {
	return List;
}