#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main ()
{
  set<int> set1 = {5, 3, 6, 2, 4, 1};
  set<int> set2 = {4, 2, 6, 10, 8};

  cout << "set1 = ";
  for (auto elem : set1) {
    cout << elem << " ";
  } cout << endl;

  cout << "set2 = ";
  for (auto elem : set2) {
    cout << elem << " ";
  } cout << endl;

  set<int> unionSet;
  set<int> intersectSet;
  set<int> diffSet;

  set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(unionSet, unionSet.begin()));

  cout << "union = ";
  for (auto elem : unionSet) {
    cout << elem << " ";
  } cout << endl;

  set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(intersectSet, intersectSet.begin()));

  cout << "intersection = ";
  for (auto elem : intersectSet) {
    cout << elem << " ";
  } cout << endl;

  set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(diffSet, diffSet.begin()));

  cout << "difference (set1-set2) = ";
  for (auto elem : diffSet) {
    cout << elem << " ";
  } cout << endl;

  return 0;
}
