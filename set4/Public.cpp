// C++ program to demonstrate public inheritance
// Ref: geeksforgeeks.org

#include <iostream>
using namespace std;

class Base {
private:
    int pvt = 1;

protected:
    int prot = 2;

public:
    int pub = 3;

    // method to access private member
    int getPVT() { return pvt; }
};


class PublicDerived : public Base {
public:
    // function to access protected member from Base
    int getProt() { return prot; }
};


int main()
{
    PublicDerived object1;
    cout << "Private = " << object1.getPVT() << endl;
    cout << "Protected = " << object1.getProt() << endl;
//    cout << "Protected = " << object1.prot << endl;
    cout << "Public = " << object1.pub << endl;

    return 0;
}
