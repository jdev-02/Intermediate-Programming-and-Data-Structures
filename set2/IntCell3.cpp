#include "IntCell.h"
#include <iostream>

using namespace std;

// constructor
IntCell::IntCell(int initialValue)
  : storedValue (initialValue) {}

// member functions
int IntCell::read() const {
  return storedValue;

}

void IntCell::write(int x) {
  storedValue = x;
}

//we could also have a predicate methods here, where we would answer a yes/no question about the data member
//utility functions can be added like print()
//you can also add in operators to overwrite the default behavior of operators like +, -, *, /, etc.


int main ()
{
  IntCell obj1;
  IntCell obj2 (12);
  cout << "obj1 value: " << obj1.read() << endl;
  cout << "obj2 value: " << obj2.read() << endl;
  obj1.write(15);
  cout << "obj1 value: " << obj1.read() << endl;

  return 0;
}
