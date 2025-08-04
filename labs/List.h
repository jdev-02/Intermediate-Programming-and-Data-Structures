// Jonathan Goohs
// Intermediate Programming and Data Strcutures Lab 1
//This is the header file for the List class which implements a singly linked list.
//It includes methods for inserting a list from the start, removing the first occurrence of a provided value,
//counting the occurrences of a value, and printing the list. It also has a destructor to clean memory dynamically allocated for the given list.

#include "ListNode.h"
#include <iostream>

#ifndef LIST_H
#define LIST_H

#define NODE_FOUND 1
#define NODE_NOT_FOUND 0

//Class template for Linked List Node

template<class T>
class List
{
public: //constructors
	//default
	List() : first(nullptr), last(nullptr), total(0) {}
	//defined constructor
	List(T& t) : first(new ListNode<T>(t, nullptr)), last(nullptr), total(1) {}
	//destructor
	~List();

	//insert method insert the value t into the front of the list only (copy variation 4 from notes)
	void insert(T t);
	int remove(T& t);
	//return the error code or not, but pass back the value of t by reference
	int count(T& t);  
	void print(); //return list of all elements

protected:
	ListNode<T>* first;
	ListNode<T>* last;
	int total;
	//to instinatiate new list nodes via friendship relationship
	ListNode<T>* newNode(T& t, ListNode<T>* next);

};

//implementation here and then the .cpp file will have the main function with interactions from the user

//newnode method implementation
template<class T>
ListNode<T>* List<T>::newNode(T& t, ListNode<T>* next) {
	//create memory for a new listnode with t data stored in it and point the next pointer to the following node
	return new ListNode<T>(t, next);
}

template<class T>
void List<T>::insert(T t) {
	//create a new node with the value t and push the first one down and point the new node to the first node
	ListNode<T>* newnode = newNode(t, first);
	//set the first node to the new node
	first = newnode;
	if (last == nullptr) {
		//the size is 1 bc last is null still, so this handles the start case
		last = newnode;
	}
	//increment total count of nodes in list
	total++;
}

template<class T>
int List<T>::remove(T& t) {
	ListNode<T>* current = first;
	ListNode<T>* prev = nullptr;
	//traverse through the list
	while (current != nullptr) {
		//if we find the value t in the current node
		if (current->data == t) {
			//special handling removing the first node if it matches
			if (prev == nullptr) {
				first = current->next;
				//essentially skipping over the first node here by pointing the first node to the next node
			} else {
				//anything but the first node
				prev->next = current->next;
				//point the previous nodes next pointer to the current nodes next pointer which skips current node
			} //update last pointer if we're removing the last node
			if (current == last) {
				last = prev;
				//if current is last then make the prev be last by kicking off the last node
			}
			delete current;
			//free memory and then decrement count of nodes in list class data member
			this->total--;
			return NODE_FOUND;
		}
		//move to the next node if not found
		prev = current;
		current = current->next;
	}
	//done traversing and found no match
	return NODE_NOT_FOUND;
}

template<class T>
int List<T>::count(T& t) {
	//return the count of how many times the given value t is seen in the list
	//traverse through the list and then add to a counter and return the counter
	int count = 0;
	ListNode<T>* current = first;
	while (current != nullptr) {
		if (current->data == t) {
			count++;
		}
		current = current->next;
	}
	return count;
}

template<class T>
void List<T>::print() {
	ListNode<T>* current = first;
	while (current != nullptr) {
		std::cout << current->data << " "; //accessing protected data member of ListNode 
		current = current->next; //accessing protected next pointer of ListNode to move to next node
	}
	//print the data of the current node in the list and then move to the next list until reaching the end
}

template<class T>
List<T>::~List() {
	//need to build destrcutor to delete the linked list since it was dynamically allocated with new
	ListNode<T>* current = first;
	while (current != nullptr) {
		//doesnt matter which order we delete with so long as we delete current and keep track of the next node until we reach the end
		if (current == last) {
			last = nullptr; //size of one
		}
		ListNode<T>* nextnode = current->next;
		//move to the next node
		delete current;
		current = nextnode;
	}
}
#endif


//EOF 