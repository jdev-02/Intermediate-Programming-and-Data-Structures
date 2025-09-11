//starting in the top left corner of a 2x2 grid, and only being able to move to right and down
//there are 6 routes to bottom right corner
//how many such routes are there through a 20x20 grid?
#include <iostream>
#include <vector>
using namespace std;

int main() {
	const int GRID_SIZE = 4;
	char grid[GRID_SIZE][GRID_SIZE];
	grid[GRID_SIZE][GRID_SIZE] = 1;
	int sum_routes = 0;
	for (int i = 0; i <= GRID_SIZE; i++) {
		for (int j = 0; j <= GRID_SIZE; j++) {
			if (grid[GRID_SIZE][GRID_SIZE] == 1) {
				sum_routes++;
			}
		}
	}
	cout << "sum of 20x20: " << sum_routes << endl;
	return 0;
}