//145 is a curious number as 1! + 4! + 5! = 1 + 24 + 120 = 145. find the sum of all numbers which are equal to the sum of the factorial of their digits
#include <iostream>
#include <vector>
#include <string>
int main() {
    // Precompute factorials for digits 0-9
    std::vector<int> fact(10, 1);
    for (int i = 1; i <= 9; i++) {
        fact[i] = fact[i - 1] * i;
    } //gives us list of [1,2,3,4,5,6,7,8
    
    int upperBound = 7 * fact[9]; // 2540160
    long long total = 0;

    for (int n = 10; n <= upperBound; n++) { // exclude 1 and 2
        int sum = 0, temp = n;
        while (temp > 0) {
            int digit = temp % 10;
            sum += fact[digit];
            temp /= 10;
        }
        if (sum == n) {
            std::cout << "Found curious number: " << n << std::endl;
            total += n;
        }
    }

    std::cout << "Sum of all curious numbers: " << total << std::endl;
    return 0;
}

