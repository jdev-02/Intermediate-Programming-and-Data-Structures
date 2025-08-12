#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> set1;
  set<int> set2 = {5, 3, 2, 4, 1};
  set<int> set3 = {1, 2, 3, 4, 6};

  if (set1 == set2) {
    cout << "Sets 1 & 2 are equal" << endl;
  } else {
    cout << "Sets 1 & 2 are not equal" << endl;
  }

  if (set2 < set3) {
    cout << "Set2 is lexicographically less than set3" << endl;
  } else {
    cout << "Set2 is lexicographically greater than set3" << endl;
  }

  if (set2 <=> set3 == 0) {
    cout << "The sets are equal" << endl;
  } else if (set2 <=> set3 < 0) {
    cout << "set2 is less than set3" << endl;
  } else if (set2 <=> set3 > 0) {
    cout << "set2 is greater than set3" << endl;
  }

  return 0;
}
