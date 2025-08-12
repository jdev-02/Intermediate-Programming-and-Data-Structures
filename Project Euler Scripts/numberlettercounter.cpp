#include <iostream>
#include <string>
#include <vector>

// Use the standard namespace to avoid prefixing with std::
using namespace std;

// Use const for data that doesn't change.
const vector<string> units = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
const vector<string> teens = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
const vector<string> tens = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

/**
 * @brief Converts an integer from 1-1000 into its English word representation.
 * * Note: Spaces and hyphens are omitted to match the problem's counting rules.
 * For example, 342 becomes "threehundredandfortytwo".
 * @param n The integer to convert.
 * @return A string with the number in words.
 */
string numberToWords(int n) {
    if (n == 1000) {
        return "onethousand";
    }

    string words = "";

    // Handle hundreds place
    if (n >= 100) {
        words += units[n / 100] + "hundred";
        n %= 100; // Get the remainder
        // British English uses "and" after hundred, as per the problem's convention.
        if (n > 0) {
            words += "and";
        }
    }

    // Handle tens and units place
    if (n >= 20) {
        words += tens[n / 10];
        words += units[n % 10];
    }
    else if (n >= 10) {
        // Numbers 10-19 are special cases
        words += teens[n - 10];
    }
    else if (n > 0) {
        words += units[n];
    }

    return words;
}

int main() {
    long totalLetterCount = 0; // Use long to be safe, though int is sufficient here.

    for (int i = 1; i <= 1; ++i) {
        string word = numberToWords(i);
        totalLetterCount += word.length();
    }

    cout << "The total number of letters used from 1 to 1000 is: " << totalLetterCount << endl;
    // The correct output is 21124

    return 0;
}