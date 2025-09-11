//2^15 = 32768 and the sum of its digits is 3+2+7+6+8 = 26
//what is the sum of the digits of the number 2^1000?

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Represent 2^0 = 1 as starting digits
    vector<int> digits(1, 1);

    // Multiply by 2 a total of 1000 times
    for (int exp = 0; exp < 1000; exp++) {
        int carry = 0;
        for (size_t i = 0; i < digits.size(); i++) {
            int val = digits[i] * 2 + carry;
            digits[i] = val % 10;   // keep the ones place
            carry = val / 10;       // carry the tens place
        }
        if (carry > 0) {
            digits.push_back(carry);
        }
    }

    // Sum all digits
    int sum = 0;
    for (int d : digits) {
        sum += d;
    }

    cout << "Sum of digits of 2^1000 = " << sum << endl;
    return 0;
}
