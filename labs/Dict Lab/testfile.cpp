//test file for custom dictionary template lab
//jonathan goohs  
//data structures and intermediate programming

#include <iostream>
#include "MyDictionary.h"
#include <string>

using namespace std;

#define FAILURE 0
#define SUCCESS 1

int main() {
    cout << "=== Testing MyDictionary with int values ===" << endl;

    MyDictionary<int> d2;  // values are int (works with returning 0)

    // Test integer dictionary
    d2.insert(0, 42);
    d2.insert(1, 1337);
    d2.insert(17, 999);  // Will hash to same bucket as key 0
    d2.insert(-5, 123);  // Test negative key handling

    cout << "Int dictionary length: " << d2.length() << endl;
    cout << "Value at key 0: " << d2.get(0) << endl;
    cout << "Value at key 17: " << d2.get(17) << endl;
    cout << "Value at negative key -5: " << d2.get(-5) << endl;

    //test non-existent key - should return 0
    cout << "Value at key 999 (non-existent): " << d2.get(999) << endl;

    cout << "Keys in int dictionary: ";
    d2.keys().printkeys();
    cout << endl;

    cout << "Values in int dictionary: ";
    d2.values().printvals();
    cout << endl;

    //test removal from int dictionary
    int removedInt = d2.remove(1);
    cout << "Removed value from key 1: " << removedInt << endl;
    cout << "Final int dictionary length: " << d2.length() << endl;

    //test removing non-existent key - should return 0
    cout << "\nTesting removal of non-existent key..." << endl;
    int nonExistentRemove = d2.remove(999);
    cout << "Attempted to remove key 999 (non-existent), returned: " << nonExistentRemove << endl;
    cout << "Dictionary length unchanged: " << d2.length() << endl;

    // Test duplicate key insertion
    cout << "\nTesting duplicate key insertion..." << endl;
    d2.insert(100, 555);
    d2.insert(100, 777);  // This will add another entry
    cout << "Length after duplicate inserts: " << d2.length() << endl;
    cout << "Value for key 100: " << d2.get(100) << endl;  // Will return the first found

    cout << "\n=== All tests completed ===" << endl;

    // Note: Testing with string would cause compilation errors when trying to return 0
    // as per teacher's guidance - that's the user's responsibility to use appropriate types

    return SUCCESS;
}