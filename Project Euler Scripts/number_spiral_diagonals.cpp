#include <iostream>
using namespace std;

// Calculate diagonal sum using the mathematical pattern for center-outward spirals
long long calculateDiagonalSum(int size) {
    // For a center-outward spiral starting with 1 at center
    // The diagonal sum can be calculated layer by layer

    long long sum = 1; // Center value is always 1

    // Number of complete layers beyond the center
    int max_layer = (size - 1) / 2;

    // For each layer, add the contribution to diagonal sum
    for (int layer = 1; layer <= max_layer; layer++) {
        // In a center-outward spiral, each layer contributes 4 values to the diagonals
        // These values are at the corners of the layer's square

        // The side length of the square for this layer
        int side = size;

        // The highest number in this layer (bottom-right corner)
        long long top_right = (long long)side * side;

        // The other three corner values (going counter-clockwise)
        long long top_left = top_right - (side - 1);
        long long bottom_left = top_left - (side - 1);
        long long bottom_right = bottom_left - (side - 1);

        // Add all four corner values to the sum
        sum += top_right + top_left + bottom_left + bottom_right;
    }

    return sum;
}

// Optimized version using direct mathematical formula
long long fastDiagonalSum(int size) {
    // The sum of diagonals in center-outward spiral follows:
    // Sum = 1 + 4 * (sum from layer=1 to n of: (2*layer+1)^2 - 6*layer)
    // where n = (size-1)/2

    if (size == 1) return 1;

    long long sum = 1; // Center
    int n = (size - 1) / 2;

    for (int layer = 1; layer <= n; layer++) {
        long long side = 2 * layer + 1;
        long long contribution = 4 * side * side - 24 * layer;
        sum += contribution;
    }

    return sum;
}

// Most efficient: Closed form mathematical solution
long long closedFormSum(int size) {
    // For center-outward spiral, the closed form is:
    // Sum = (4n^4 + 3n^2 + 8n - 9) / 6 + 1 where n = (size+1)/2

    if (size == 1) return 1;

    long long n = (size + 1) / 2;
    return (4 * n * n * n * n + 3 * n * n + 8 * n - 9) / 6 + 1;
}

// Direct calculation using the known pattern
long long directCalculation(int size) {
    // Based on the pattern: diagonal sum = (4n^4 + 4n^3 + 4n^2 + 4n + 1)
    // where n = (size - 1) / 2

    long long n = (size - 1) / 2;
    long long n2 = n * n;
    long long n3 = n2 * n;
    long long n4 = n3 * n;

    return 4 * n4 + 4 * n3 + 4 * n2 + 4 * n + 1;
}

int main() {
    cout << "=== Center-Outward Spiral Diagonal Sum ===" << endl;
    cout << endl;

    // Test with 5x5 to verify correctness
    cout << "Testing with 5x5 spiral (expected: 101):" << endl;
    cout << "Method 1: " << calculateDiagonalSum(5) << endl;
    cout << "Method 2: " << fastDiagonalSum(5) << endl;
    cout << "Method 3: " << closedFormSum(5) << endl;
    cout << "Method 4: " << directCalculation(5) << endl;
    cout << endl;

    // Calculate for 1001x1001
    cout << "Calculating diagonal sum for 1001x1001 spiral:" << endl;
    long long answer = directCalculation(1001);
    cout << "Result: " << answer << endl;
    cout << endl;

    // Verification with other methods
    cout << "Verification:" << endl;
    cout << "Method 1: " << calculateDiagonalSum(1001) << endl;
    cout << "Method 4: " << directCalculation(1001) << endl;
    cout << endl;

    cout << "ANSWER: " << answer << endl;

    return 0;
}