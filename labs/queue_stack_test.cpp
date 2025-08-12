//Jonathan Goohs
//Intermediate Programming and Data Structures Lab 
//This is the test file and main function for the Queue and Stack derivative classes from the List class.
//I have tested all methods with different types and lengths of classes.

#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

#define FAILURE 0
#define SUCCESS 1

int main() {
    //empty list
    Stack<int> s1;
    int val1 = 42;
    //s1.print();
    s1.push(val1);
    //s1.print();
    s1.push(val1 + 1);
    
    //s1.print();
    cout << s1.pop() << endl; // Should print 43
    //s1.print();//should print 42 only
    cout << s1.pop() << endl;
    s1.print();//should throw exception?
	cout << "Is stack empty? " << (s1.isEmpty() ? "Yes" : "No") << endl; // Should print Yes
    //cout << s1.pop() << endl;

    s1.print();

    Queue<string> q1;
    q1.enqueue("Hi");
	q1.enqueue("Hello");
    q1.print();
    cout << q1.isEmpty() << endl;
    cout << q1.dequeue() << endl;
    q1.print();
	q1.dequeue();
    q1.print();
}