//starting in the top left corner of a 2x2 grid, and only being able to move to right and down
//there are 6 routes to bottom right corner
//how many such routes are there through a 20x20 grid?
#include <iostream>
using namespace std;

// Function to compute n choose k using an iterative approach
unsigned long long binomialCoefficient(int n, int k) {
    if (k > n - k) k = n - k; // Take advantage of symmetry
    unsigned long long result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= (n - k + i);
        result /= i;
    }
    return result;
}

int main() {
    int gridSize = 20;
    unsigned long long paths = binomialCoefficient(2 * gridSize, gridSize);

    cout << "Number of lattice paths in a " << gridSize
        << "x" << gridSize << " grid is: "
        << paths << endl;

    return 0;
}
