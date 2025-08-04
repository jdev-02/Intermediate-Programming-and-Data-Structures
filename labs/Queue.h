#include "List.h"
#ifndef Stack_h
#define Stack_h

stack implementation - removeFront() in LIst :
in stack, for pop() we are removing from the front
queue implementation - removeFront() in List :
in queue, for pop() we are removing from the front

instructions :
make stack and then make a copy#pragma once

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

#endif