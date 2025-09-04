//digitsumnumbers
#include <iostream>
using namespace std;
//The Combinatorial Method(Construct - and -Sum)
//How it works : Loop through the possible structures of a DS - number(e.g., "a 5-digit number whose special digit is 7").
//Recursive Task : For each structure, find the combinations of the other digits that fit the required sum.
//Action : For each valid combination found, calculate its contribution to the total sum.
// Result : Succeeds because it never wastes time on invalid structures.
//find S(2020), giving answer in modulo 10^16

