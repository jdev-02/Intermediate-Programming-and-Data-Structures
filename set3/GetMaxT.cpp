#include <iostream>

using namespace std;

template <typename T>

T GetMax (T a, T b) {
  T result = (a > b) ? a : b;
  return (result);
}


int main ()
{
  int    i1 = 5,       i2 = 6,       i3;
  float  f1 = 10.5,    f2 = 1.5,     f3;
  string s1 = "hello", s2 = "world", s3;

  i3 = GetMax<int>    (i1, i2);
  f3 = GetMax<float>  (f1, f2);
  s3 = GetMax<string> (s1, s2);

  cout << "max of " << i1 << " and " << i2 << " is " << i3 << endl;
  cout << "max of " << f1 << " and " << f2 << " is " << f3 << endl;
  cout << "max of " << s1 << " and " << s2 << " is " << s3 << endl;

  return 0;
}
