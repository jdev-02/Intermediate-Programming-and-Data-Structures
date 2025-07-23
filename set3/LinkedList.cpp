#include <iostream>
using namespace std;

// This is a template class for a node in a linked list.
// 'T' means it can store any data type (like int, double, etc.).
    template<class T>
class ListNode
{
  public:
    // Constructor: creates a node with data 't' and a pointer to the next node 'p'.
    ListNode (T& t, ListNode<T> *p) : data (t), next (p) {}

  protected:
    T data;                 // The value stored in this node.
    ListNode<T> *next;      // Pointer to the next node in the list.
};


int main ()
{
  int number;               // Variable to store user input.
  int count = 0;            // Counts how many nodes are in the list.
  ListNode<int> *start, *temp; // Pointers to the start of the list and a temporary node.
  start = nullptr;          // Start with an empty list (no nodes yet).

  // Keep asking the user for numbers until they enter 0 or a negative number.
  while (true) {
    cout << "Enter number (0 to stop): "; 
    cin >> number;
    if (number <= 0) break; // Stop if the user enters 0 or less.

    temp = start; // Remember the current first node.

    // Create a new node with the entered number.
    // The new node points to the previous first node.
    start = new ListNode<int>(number, temp);
    count++; // Increase the count of nodes.
  }

  // Print out how many numbers were entered (size of the list).
  cout << "Total size of list is " << count << endl;

  return 0;
}
