//the fibonacci sequence is defined by fn = fn-1 + fn-2 where f1 =1 and f2 = 1.
//the 12th term f12 is the first term to contain three digits
// what is the index of the first term in the fibonacci sequence to contain 1000 digits?
//f1 = 1
//f2 = 1
//f3 = 2
//f4 = 3
//f5 = 5
//f6 = 8
//f7 = 13
//f8 = 21
//f9 = 34
//f10 = 55
//f11 = 89
//f12 = 144
//so the input would be 3 and the output would be12 

#include <iostream>
#include <vector>
#include <string>
using namespace std;


string addStrings(const string& num1, const string& num2) {
    string result = "";
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;

        i--;
        j--;
    }

    return result;
}

int findFibonacciIndexWithNDigits(int n) {
    if (n == 1) return 1;

    string f1 = "1", f2 = "1";
    int index = 2;

    while (f2.length() < n) {
        string next = addStrings(f1, f2);
        f1 = f2;
        f2 = next;
        index++;
    }
    return index;
}


int main() {
	int n = 1000;
	int answer = findFibonacciIndexWithNDigits(n);
	cout << answer << " is the index of first term with " <<  n << " digits" << endl;
	return 0;
}