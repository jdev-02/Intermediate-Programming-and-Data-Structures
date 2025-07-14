#include <iostream>
using namespace std;

class IntCell {

  public:

    explicit IntCell(int initialValue = 0)
	  : storedValue (initialValue){}

    int read()
      { return storedValue; }

    void write(int x)
      { storedValue = x; }

  private:

    int storedValue;

};


int main ()
{

  IntCell obj1;
  IntCell obj2 (12);
//  IntCell obj3 = 37;    //throws error
//  IntCell obj4 ();    //throws warning

  cout << "obj1 value: " << obj1.read() << endl;
  cout << "obj2 value: " << obj2.read() << endl;
//  cout << "obj3 value: " << obj3.read() << endl;
//  cout << "obj4 value: " << obj4.read() << endl;

//  obj1 = 10;    //throws error
//  cout << "obj1 value: " << obj1.read() << endl;

//  int x = obj2;  //throws error
//  obj1 = x;
//  cout << "obj1 value: " << obj1.read() << endl;

  return 0;
}
