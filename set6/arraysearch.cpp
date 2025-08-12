#include <iostream>
using namespace std;

bool search (int arr[], int val, int length, int pos=0);

int main ()
{
  int array[5] = {86, -1, 42, 13, 86};
  int arrsize = size(array);
  int num1 = 42;
  int num2 = 41;
  bool result;

  result = search(array, num1, arrsize);
  if (result) { cout << num1 << " found in array" << endl; }
  else { cout << num1 << " not found in array" << endl; }

  result = search(array, num2, arrsize);
  if (result) { cout << num2 << " found in array" << endl; }
  else { cout << num2 << " not found in array" << endl; }

  return 0;

}


bool search (int arr[], int val, int length, int pos) {

  if (pos == length) { return false; }
  else if (arr[pos] == val) { return true; }
  // recursive call
  else { return search(arr, val, length, pos+1); }

} //end search
