//Jonathan Goohs
//Intermediate Programming and Data Structures Lab 1
//This is the test file and main function for the List class.
//I have tested all methods with different types and lengths of classes.

#include "List.h"

using namespace std;
#define FAILURE 0
#define SUCCESS 1

int main() {
    //empty list
    List<int> emptyList;
    int val1 = 42;
    emptyList.print();
    cout << emptyList.count(val1) << endl;
    cout << emptyList.remove(val1) << endl;

    //single element list
    List<int> singleList;
    int val2 = 99;
    singleList.insert(val2);
    singleList.print();
    cout << singleList.remove(val2) << endl;
    singleList.print();
//head and tail and middle remoal
    List<int> testList;
    int v1 = 1, v2 = 2, v3 = 3;
    testList.insert(v1);
    testList.insert(v2);
    testList.insert(v3); // List: 3 2 1
    testList.remove(v3); // Remove head
    testList.remove(v1); // Remove tail
    testList.remove(v2); // Remove middle (now only one left)
    testList.print();

    // Test with other types
    List<string> strList;
    string s1 = "hello", s2 = "world";
    strList.insert(s1);
    strList.insert(s2);
    strList.print();
    return SUCCESS;
}