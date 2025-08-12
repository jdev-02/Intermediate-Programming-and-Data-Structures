#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> set1 = {2, 4, 1, 5, 3};

  auto item1 = set1.begin();
  auto item2 = next(item1, 2);

  cout << *item1 << " " << *item2 << endl;

  item1 = set1.end();
  item2 = next(item1, -2);

  cout << *item1 << " " << *item2 << endl;

  return 0;
}
