#include <iostream>
using namespace std;

class IntCell {

  public:

    IntCell()
      { storedValue = 0; }
    //constructor

    IntCell(int initialValue)
      { storedValue = initialValue; }
    //constructor

    int read()
      { return storedValue; }
    //public methods
    void write(int x)
      { storedValue = x; }
    //public methods
  private:

    int storedValue;

};


int main ()
{
  IntCell* obj1 = new IntCell(42);
  IntCell obj1;
  IntCell obj2 (12);
  IntCell obj3 = 37;    //should throw error, but doesn't bc it makes an implicit conversion from an int
//  IntCell obj4 ();    //throws warning

  cout << "obj1 value: " << obj1->read() << endl;
  cout << "obj1 value: " << obj1.read() << endl;
  cout << "obj2 value: " << obj2.read() << endl;
  cout << "obj3 value: " << obj3.read() << endl;
//  cout << "obj4 value: " << obj4.read() << endl;    //throws error

  obj1 = 10;    //should throw error, but doesn't
  cout << "obj1 value: " << obj1.read() << endl;

//  int x = obj2;  //throws error
//  obj1 = x;
//  cout << "obj1 value: " << obj1.read() << endl;

  return 0;
}
