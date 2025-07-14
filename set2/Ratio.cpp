#include <iostream>

using namespace std;

class Ratio
{
	public:
		Ratio(): num (0), den (1) {}
		Ratio (int n): num (n), den (1) {}
		Ratio (int n, int d): num (n), den (d) {}

        // domain-specific method to print fraction
		void print() { cout << num << "/" << den; }

	private:
		int num, den;

};


int main()
{
	Ratio x, y (7), z (-1, 3);

	cout << "x = ";
	x.print();
	cout << " and y = ";
	y.print();
	cout << " and z = ";
	z.print();
	cout << endl;

	return 0;
}
