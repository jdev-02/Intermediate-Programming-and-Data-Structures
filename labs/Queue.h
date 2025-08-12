// Jonathan Goohs
// Intermediate Programming and Data Strcutures Lab 2
//This is the header file for the Queue derivative class which implements a Queue data structure using a linked list.
//It includes methods for enqueuing an item, dequeuing an item, checking if the queue is empty, and printing the queue contents from back to front.

#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

//queue interface

template <class T>
class Queue : public List<T> //public inheritance from List of type T
{
public:
	//using List<T>::List; would inherit all constructor s
	void enqueue(T item);

	T dequeue();

	bool isEmpty();

	void print();
};

//queue implementation

template <class T>
void Queue<T>::enqueue(T item) {
	//setter method to add given data element onto the end of the queue (or the front of the linked list)
	this->insert(item);
}

template <class T>
T Queue<T>::dequeue() {
	//a getter method to remove and return the oldest element in the queue, which is the same as removing from the end of the linked list
	//removeFront will throw exception if the queue is empty so no need to handle that here
	return this->removeEnd();
}

template <class T>
bool Queue<T>::isEmpty() {
	//returns a boolean value indicating whether the queue is empty
	//reference the first pointer of the linked list and if its null we have already setup such that the list is empty
	if (this->first == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void Queue<T>::print() {
	//prints out data contents of the queue from back to front, which is the same as printing the linked list from the front to the end
	List<T>::print();
}

#endif

//EOF