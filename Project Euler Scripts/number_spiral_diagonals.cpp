//starting with the number 1 and moving to the right in a clockwise direction for 
//a 5x5 spiral forms the sum of numbers of the diagonals is 101 (so the x pattern of the spiral)
//what is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in same way?
#include <iostream>
#include <vector>
using namespace std;


// 2D Vector Size Explanation and Printing
void print2DVector(const vector<vector<int>>& matrix) {
    cout << "Matrix visualization:" << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "\t";  // \t for tab spacing
        }
        cout << endl;
    }
    cout << endl;
}

/*void vectorSizeExplanation() {
    vector<vector<int>> matrix(5, vector<int>(5));

    // Fill with simple numbers to see structure
    int counter = 1;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = counter++;
        }
    }

    // Size explanations:
    cout << "matrix.size() = " << matrix.size() << endl;           // Returns 5 (number of rows)
    cout << "matrix[0].size() = " << matrix[0].size() << endl;     // Returns 5 (number of columns in row 0)

    // Total elements calculation:
    int totalElements = matrix.size() * matrix[0].size();
    cout << "Total elements = " << totalElements << endl;          // 5 * 5 = 25

    cout << endl;
    print2DVector(matrix);

    // Alternative printing with row/column labels:
    cout << "With indices:" << endl;
    cout << "   ";
    for (int j = 0; j < matrix[0].size(); j++) {
        cout << "C" << j << "\t";
    }
    cout << endl;

    for (int i = 0; i < matrix.size(); i++) {
        cout << "R" << i << " ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Example of basic vector operations
//void vectorBasics() {
    // Creating vectors
    //vector<int> vec1;                    // Empty vector
    //vector<int> vec2(5);                // Vector with 5 elements (default 0)
    //vector<int> vec3(5, 10);            // Vector with 5 elements, all set to 10
    //vector<int> vec4 = { 1, 2, 3, 4, 5 }; // Initialize with values

    // Adding elements
    //vec1.push_back(42);
    //vec1.push_back(84);

    // Accessing elements
    //cout << "First element: " << vec1[0] << endl;
    //cout << "Second element: " << vec1.at(1) << endl; // safer with bounds checking

    // Size and capacity
    //cout << "Size: " << vec1.size() << endl;
    //cout << "Capacity: " << vec1.capacity() << endl;

    // Iterating through vector
    //for (int i = 0; i < vec1.size(); i++) {
    //    cout << vec1[i] << " ";
    //}
    //cout << endl;

    // Range-based for loop (C++11+)
    //for (const auto& element : vec1) {
    //    cout << element << " ";
    //}
    //cout << endl;
//}
*/

// CENTER-OUTWARD SPIRAL: Starting from center
vector<vector<int>> makematrix(int x, int y) {
    vector<vector<int>> matrix(x, vector<int>(y)); // Creates x rows, y columns

    // For center-outward spiral, starting position is the CENTER
    int centerRow = x / 2;    // For 5x5: centerRow = 2
    int centerCol = y / 2;    // For 5x5: centerCol = 2

    int counter = 1;
    // Place first element at center
    matrix[centerRow][centerCol] = counter++;

    // For center-outward spiral, you need to think in "layers" or "rings"
    // Layer 0: just the center (1 element)
    // Layer 1: the 8 elements around the center
    // Layer 2: the 16 elements around layer 1, etc.

    // Key insight: You move outward in expanding squares/rectangles
    // Direction pattern might be: right, down, left, left, up, up, right, right, right...
    // The number of steps increases as you spiral outward

    // This is much more complex than the simple row-by-row filling!
    // You'll need to track:
    // - Current position (row, col)
    // - Current direction (right, down, left, up)
    // - How many steps to take in current direction
    // - When to change direction and increase step count

    cout << "Starting position for center-outward spiral:" << endl;
    cout << "Center at [" << centerRow << "][" << centerCol << "]" << endl;
    cout << "This is where element 1 should be placed." << endl;

    // For now, just fill sequentially to show structure
    // (You'll replace this with actual spiral logic)
    counter = 1;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (i == centerRow && j == centerCol) {
                matrix[i][j] = 1;  // Center gets 1
            }
            else {
                matrix[i][j] = counter++;
                if (counter == 1) counter++; // Skip 1 since it's already used
            }
        }
    }

    return matrix;
}

// ISSUE 2: Diagonal logic problems
int sumdiagonals(const vector<vector<int>>& matrix) {
    int size = matrix.size();
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += matrix[i][i];                    // Left diagonal
        sum += matrix[i][size - 1 - i];         // Right diagonal (note the -1!)
    }

    // For odd-sized matrices, subtract the center once (it was counted twice)
    if (size % 2 == 1) {
        int center = size / 2; //defaults to floor when using / operator
        sum -= matrix[center][center];
    }
    return sum;
}

int main() {
    //cout << "=== Vector Basics ===" << endl;
    //vectorBasics();
    //cout << endl;

    /*cout << "=== 2D Vector Size and Visualization ===" << endl;
    vectorSizeExplanation();
    cout << endl;
    */

    cout << "=== Your Matrix Function ===" << endl;
    vector<vector<int>> v1 = makematrix(1001, 1001);

    cout << "v1.size() = " << v1.size() << " (this is the number of ROWS)" << endl;
    cout << "v1[0].size() = " << v1[0].size() << " (this is the number of COLUMNS)" << endl;
    cout << "Total elements = " << v1.size() * v1[0].size() << endl;
    cout << endl;

    cout << "Matrix contents:" << endl;
    //print2DVector(v1);

    int result = sumdiagonals(v1);
    cout << "Sum of diagonals: " << result << endl;

    return 0;
}
