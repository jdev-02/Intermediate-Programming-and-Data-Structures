#include <iostream>
using namespace std;

string reverse (string str);

int main ()
{
  string str1 = "nametag";
  string rev1 = reverse(str1);
  string str2 = "Hello world!";
  string rev2 = reverse(str2);

  cout << "Reverse of " << str1 << " is " << rev1 << endl;
  cout << "Reverse of " << str2 << " is " << rev2 << endl;

  return 0;
}


string reverse (string str) {

  if (str == "") { return str; }
  else {  //recursive call
    return reverse(str.substr(1, str.length())) + str.substr(0, 1);
  }

} //end search
