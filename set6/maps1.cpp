#include <iostream>
#include <map>
using namespace std;

int main ()
{
  map<int, string> map1;
  map<int, string> map2 = {{1,"first"}, {2,"second"}, {3,"third"}};

  map1.insert({1,"First"});
  map2.insert({2,"Second"});  // ignored, can't reinsert
  map2.erase(2);
  map2.erase(2);  // ignored, no key 2

  cout << "map1:" << endl;
  for (auto i : map1)
    cout << i.first << " " << i.second << endl;

  cout << endl << "map2:" << endl;
  for (auto i : map2)
    cout << i.first << " " << i.second << endl;

  return 0;
}
