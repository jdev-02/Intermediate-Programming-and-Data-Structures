#include <iostream>
using namespace std;

template<class T>
class ListNode
{
  public:  //constructor
    ListNode (T& t, ListNode<T> *p) : data (t), next (p) {}

  protected:
    T data;
    ListNode<T> *next;
};


int main ()
{
  int number;
  int count = 0;
  ListNode<int> *start, *temp;
  start = nullptr;

  // start asking for numbers...
  while (true) {
    cout << "Enter number (0 to stop): "; cin >> number;
    if (number <= 0) break;
    temp = start; //remember current front node

    // create a new node
    start = new ListNode<int>(number, temp);
    count++;
  }

  cout << "Total size of list is " << count << endl;

  return 0;
}
