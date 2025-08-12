#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> set1 = {2, 4, 1, 5, 3};

  auto item1 = set1.find(3);
  auto item2 = set1.find(6);  // not in set1

  if (item1 != set1.end()) cout << *item1 << " in set1" << endl;
  if (item2 != set1.end()) cout << *item2 << " in set1" << endl;

  return 0;
}
