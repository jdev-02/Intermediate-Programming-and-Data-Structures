class IntCell {
public:
	//public access specifier
	IntCell()
		//constructor
	{
		storedValue = 0;
	}
	IntCell(int initialValue)
		//constructor
	{
		storedValue = initialValue;
	}
	int read()
		//member function
	{
		return storedValue;
	}
	void write (int x)
		//member function
	{
		storedValue = x;
	}
private:
	//private access specifier
	int storedValue;
	//data member
};