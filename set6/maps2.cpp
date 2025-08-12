#include <iostream>
#include <map>
using namespace std;

int main ()
{
  map<int, string> map1;
  map<int, string> map2 = {{1,"first"}, {2,"second"}, {3,"third"}};

  auto it1 = map1.find(2);
  auto it2 = map2.find(2);

  if (it1 != map1.end())
    cout << it1->first << " " << it1->second << endl;
  else
    cout << "Key not found" << endl;

  if (it2 != map2.end())
    cout << it2->first << " " << it2->second << endl;
  else
    cout << "Key not found" << endl;

  map2.at(1) = "First";
  it2 = map2.find(1);

  if (it2 != map2.end())
    cout << it2->first << " " << it2->second << endl;
  else
    cout << "Key not found" << endl;

  return 0;
}
