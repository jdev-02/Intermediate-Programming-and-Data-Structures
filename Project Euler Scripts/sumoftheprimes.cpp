//sum of the primes below 10 is 2 + 3 + 5 + 7 = 17
//find the sum of the primes below two million
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int j = 2; j * j <= n; j++) {
        if (n % j == 0) return false;
    }
    return true;
}

long long sumPrimesBelowN(int N) {
    long long sum = 0;
    for (int i = 2; i < N; i++) {
        if (isPrime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    cout << sumPrimesBelowN(2000000) << endl; // should bbe 17
}