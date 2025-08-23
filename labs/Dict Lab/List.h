// File: List.h
//
// Author: Al Shaffer
//
// This file defines a List class template for a linked list that
// uses a list node class template called ListNode. This file is
// used for MyDictionary class, CS3021 Assignment 3.

#include <iostream>
using namespace std;

#ifndef List_h
#define List_h

template<class T> class List;	// forward reference to List class

// *****Linked List Node Class*****
template<class T>
class ListNode
{
    friend class List<T>;

	public:
		ListNode(int k, T& v, ListNode<T>* p): key(k), value(v), next(p) {}

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
		void insert(T t);	    //insert t at front of list
		int remove(T& t);       //remove instance of t from list
		void print();           //traverse list and print every list value
    	int total;				//total number nodes in list

};


// *****List Class Implementation*****
template<class T>
List<T>::~List()
{
	ListNode<T>* p = first;

	while (p != 0) {
		p = p->next;
		delete first;
		first = p;
	}
}


template<class T>
void List<T>::insert(T t)
{
	ListNode<T>* p = newNode(t, first);
	first = p;
	if (first->next == nullptr) { last = p; }
	total++;
}


template<class T>
int List<T>::remove(T& t)
{
	ListNode<T> *prev, *del;

	del = first;

	while (del != 0 && t != del->data) {
		prev = del;
		del = del->next;
	}

	if (del == 0) { return 0; }  //value t not fount in list
	else {
		if (del == first) { first = first->next; }
		else {
			prev->next = del->next;
			if (prev->next == 0) { last = prev; }
		}
	}

	delete del;
	total--;
	return 1;  //value t found in list and removed
}


template<class T>
void List<T>::print()
{
	ListNode<T>* p = first;

	while (p != 0) {
		cout << p->data;
		if (p != last) { cout << " -> "; }
		p = p->next;
	}
}


template<class T>
ListNode<T>* List<T>::newNode(T& t, ListNode<T>* p)
{
	ListNode<T>* q = new ListNode<T>(t, p);
	return q;
}


#endif
