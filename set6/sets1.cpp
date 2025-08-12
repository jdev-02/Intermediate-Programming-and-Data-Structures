#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> set1;
  set<int> set2 = {5, 3, 2, 4, 1};

  for (auto i : set2) {
    cout << i << " ";
  } cout << endl;

  return 0;
}
