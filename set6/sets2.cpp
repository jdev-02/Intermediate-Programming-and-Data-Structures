#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> set1 = {2, 4, 1};

  for (auto i : set1) {
    cout << i << " ";
  } cout << endl;

  set1.insert(3);
  set1.insert(2);

  for (auto i : set1) {
    cout << i << " ";
  } cout << endl;

  return 0;
}
