//if we list all the natural numbers below 10 that are multiples of 3 or 5,
//We get 3,5,6,and 9. the sum of these multiples is 23.
//find the sum of all the multiples of 3 or 5 below 1000
//if number below some range mod 3 == 0 or mod 5 == 0
    //add the value of that number to a total
    //print out the sum of that value for the input of the number

#include <iostream>
using namespace std;

// Function takes value directly (pass by value)
int sumofmultiples(int limit) {
    int sum = 0;

    for (int i = 1; i < limit; i++) {
        if ((i % 3 == 0) || (i % 5 == 0)) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    cout << "Enter an integer to find sum of multiples of 3 or 5 below it: " << endl;

    int number;
    cin >> number;

    int total = sumofmultiples(number);  // Pass value directly

    if (total == 0) {
        cout << "There are no multiples of 3 or 5 below " << number << endl;
    }
    else {
        cout << "The sum of multiples of 3 or 5 below " << number << " is: " << total << endl;
    }

    return 0;
}