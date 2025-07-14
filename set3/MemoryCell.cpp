#include "MemoryCell.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{

  MemoryCell<int>    m1;
  MemoryCell<float>  m2(3.14);
  MemoryCell<string> m3("Hello");

  cout << "Initial read:" << endl;
  cout << "m1 = " << m1.read() << endl;
  cout << "m2 = " << m2.read() << endl;
  cout << "m3 = " << m3.read() << endl;

  m1.write (37);
  m2.write (m2.read() * 2);
  m3.write (m3.read() + " world!");

  cout << endl << "After write: " << endl;
  cout << "m1 = " << m1.read() << endl;
  cout << "m2 = " << m2.read() << endl;
  cout << "m3 = " << m3.read() << endl;

  return 0;
}
