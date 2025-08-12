// Jonathan Goohs
// Intermediate Programming and Data Strcutures Lab 2
//This is the header file for the Stack derivative class which implements a Stack data structure using a linked list.
//It includes methods for pushing an item onto the stack, popping an item off of the stack, checking if the stack is empty, and printing the stack contents from top to bottom.

#ifndef STACK_H
#define STACK_H

#include "List.h"

//stack interface
template <class T>
class Stack : public List<T> //public inheritance from List of type T
{
	public:
		//using List<T>::List; would inherit all constructor 
		void push(T item);

		T pop();

		bool isEmpty();

		void print();
};

//stack implementation

template <class T>
void Stack<T>::push(T item) {
	//setter method to push given data element onto the stack
	this->insert(item);
	//pushes items onto the stack (first spot in linked list as new node)
}

template <class T>
T Stack<T>::pop() {
    // removeFront() will throw if the stack is empty
    return this->removeFront();
}

template <class T>
bool Stack<T>::isEmpty() {
	//returns a boolean value indicating whether the stack is empty
	//reference the first pointer of the linked list and if its null we have already setup such that the list is empty
	if (this->first == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void Stack<T>::print() {
	//traversal of data from top to bottom of the stack, in our case this is from the front to the end of the linked list
	//this is the same logic as the print method in List so just call that
	List<T>::print();
}

#endif

//EOF