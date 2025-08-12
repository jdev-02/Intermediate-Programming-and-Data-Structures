//A recursive function includes a statement(s) that calls the function itself
void repeatOverandOver() {
	cout << "hi" << endl;
	repeatOverandOver();
}
//There must be an "end case" test to stop the recursion
//When the recursion reaches the end case, the recursion is stopped
	//otherwise, the revusion continues by making another recursive call
//we can define a recursion by making a recurrence formula:
	//factoria(n) = n*factorial(n-1) for n > 1
				//1				 for n = 1

bool search(int arr[], int val, int len, int pos = 0) {
	if (pos == len) { return false } //if pos is len that means we have went over the array since pos starts at 0
	else if (arr[pos] == val) { return true; }
	//recursive call
	else { return search(arr, val, len, pos + 1); }
}
//due to algorithm complexity, theres actually a hinderence in implementing this via recursion because of the runtime efficiency
//every time the function runs you have to create a stack frame and build on it

//heres another function
string reverse(string str) {
	if (str == "")) { return str; } //base case
	else {
		return reverse(str.substr(1, str.length())) + str.substr(0, 1);
	}
}
//same problem here, at runtime you are building up the stack 


//the classic recursion problem is the towers of hanoi
//the analogy here is that you have some sorted data 
//and you want to move it from one place to another

//rules for applying recursion
//use recursion when:
//1. a recusrive solutions is natural and easy to understand
//2. a recursive solution does not result in excessive duplicate computation
//3. the equivalent iteraive solution is too complex to implement