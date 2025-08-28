// File: List.h
//
// Author: Al Shaffer & Jonathan Goohs
//
// This file defines a List class template for a linked list that
// uses a list node class template called ListNode. This file is
// used for MyDictionary class, CS3021 Assignment 3.

#include <iostream>
using namespace std;

#ifndef List_h
#define List_h

#define KEY_NOT_FOUND 0

template<class T> class List;	// forward reference to List class

// *****Linked List Node Class*****
template<class T>
class ListNode
{
    friend class List<T>; //list is a friend of listnode

	public:
		ListNode(int k, T& v, ListNode<T>* p): key(k), value(v), next(p) {} //constructor for listnode which in this case is kv pair with k as int and T for value, singly linked with a next pointer

	protected:
		int key;				// key
		T value;				// value
		ListNode<T>* next;		// pointer to next node
};


// *****List Class Interface*****
template<class T>
class List
{
	protected:
		ListNode<T>* first;     //pointer to first node in list
		ListNode<T>* last;      //pointer to last node in list
        //method to instantiate new list node using friend relationship
        ListNode<T>* newNode(int k, T& v, ListNode<T>* p);

	public:
		List(): first(0), last(0), total(0) {}
		~List();
		void insert(int key, T& value);	    //takes kvp
		T removebyKey(int key);       //remove instance of kvp from list
		void printkeys();           //traverse list and print every dict key
		void printvals();		//traverse list and print every dict val
    	int total;				//total number nodes in list
		T getByKey(int key); //find value by key
		List<int> keys(); //this feeds the getallkeys in dict
		List<T> values(); //this feeds into getallvals in dict
		void appendFrom(List<T>& sourceList);
};


// *****List Class Implementation*****
template<class T>
List<T>::~List()
{	//destructor to free memory used by list in dict
	ListNode<T>* p = first;

	while (p != 0) {
		p = p->next;
		delete first;
		first = p;
	}
}


template<class T>
void List<T>::insert(int key, T&value)
//inserts kv at front of list and increments total
{
	ListNode<T>* p = newNode(key, value, first);
	first = p;
	if (first->next == nullptr) { last = p; }
	total++;
}


template<class T>
T List<T>::removebyKey(int key)
//removes first instance of given t from list and moves pointer accordingly
{
	ListNode<T> *prev, *del;

	del = first;

	while (del != 0 && key != del->key) {
		//while first node not null and not found the t data, move to next node
		prev = del;
		del = del->next;
	}

	if (del == 0) { return T(); }  //value t not found in list
	else {
		//value t was found so remove it by moving the pointers over the node found, if first case just move first pointer to next node
		//if otherwise (its in the middle of the list), previous node's next pointer gets the delete's next pointer
		//if the previous next pointer is null that means the 
		if (del == first) { first = first->next; }
		else {
			//its not the first node its either in the middle or the end of the list
			prev->next = del->next;
			//middle case
			if (prev->next == 0) { last = prev; }
			//last case
		}
	}
	T removedValue = del->value;  //store value before deleting
	delete del;
	total--;
	return removedValue;  //return the actual value
}


template<class T>
void List<T>::printkeys()
{
	//pointer to first node in list, traversing through and continue to add in -> until its the end
	ListNode<T>* p = first;

	while (p != 0) {
		cout << p->key;
		if (p != last) { cout << " -> "; }
		p = p->next;
	}
}

template<class T>
void List<T>::printvals()
{
	//pointer to first node in list, traversing through and continue to add in -> until its the end
	ListNode<T>* p = first;

	while (p != 0) {
		cout << p->value;
		if (p != last) { cout << " -> "; }
		p = p->next;
	}
}

template<class T>
T List<T>::getByKey(int k) {
	ListNode<T>* p = first;

	while (p != 0) {
		if (p->key == k) { return p->value; }
		p = p->next;
	} //else we have not found the key
	return KEY_NOT_FOUND;
}

template<class T>
List<int> List<T>::keys() {
	ListNode<T>* p = first;
	List<int> keysinList;
	while (p != 0) {
		int dummyVal = 0;
		keysinList.insert(p->key, dummyVal);
		p = p->next; //keep going through list
	} 
	return keysinList;
}

template<class T>
List<T> List<T>::values() {
	ListNode<T>* p = first;
	List<T> valsinList;
	while (p != 0) {
		int dummyKey = 0;
		valsinList.insert(dummyKey, p->value);
		p = p->next; //keep going through list
	} 
	return valsinList;
}
template<class T>
void List<T>::appendFrom(List<T>& sourceList) {
	//take the original list we will be appending by reference
	ListNode<T>* p = sourceList.first;
	while (p != 0) {
		this->insert(p->key, p->value);  // Insert each key-value pair
		p = p->next;
	}
}
	
template<class T>
ListNode<T>* List<T>::newNode(int k, T& v, ListNode<T>* p)
{
	//returns a pointer to a list node object
	ListNode<T>* q = new ListNode<T>(k, v, p);
	return q;
}


#endif
