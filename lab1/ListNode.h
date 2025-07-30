//Jonathan Goohs
//Intermediate Programming and Data Structures Lab 1
//This is the header file for the ListNode class which implements a singly linked list node.    

#ifndef LISTNODE_H
#define LISTNODE_H

template<class T> class List;
//this declares there will be a template class List that uses a type parameter T

template<class T>
class ListNode
{
    friend class List<T>;
public:
    // Constructor: creates a node with data 't' and a pointer to the next node 'p'.
    ListNode(T& t, ListNode<T>* p) : data(t), next(p) {}

protected:
    T data;                 // The value stored in this node
    ListNode<T>* next;      // Pointer to the next node in the list
}; 

#endif