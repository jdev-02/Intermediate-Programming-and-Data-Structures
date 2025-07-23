//a class is instatiable if we can create instances of it, like string or date classes in C++
//The math class is not instantiable, because it is a utility class that only has static methods and no data members

class MealCard {
private:
	//data memebrs
	int currentBalance;

public:
	//constructor
	MealCard(int amount) {
		currentBalance = amount;
	};

	//methods
	void add(int amount) {
		currentBalance += amount;
	}

	void deduct(int amount) {
		currentBalance -= amount;
	}

	int getBalance() {
		return this->currentBalance;
	}
};

//objects give us the ability to encapsulate information, along with the characteristics of that idea into an object
//it allows data hiding and abstraction

int main() {
    // Create a MealCard with an initial balance of 50
    MealCard myCard(50);

    std::cout << "Initial balance: " << myCard.getBalance() << std::endl;

    // Add 25 to the balance
    myCard.add(25);
    std::cout << "After adding 25: " << myCard.getBalance() << std::endl;

    // Deduct 10 from the balance
    myCard.deduct(10);
    std::cout << "After deducting 10: " << myCard.getBalance() << std::endl;

    // Deduct 100 from the balance (shows negative balance is possible)
    myCard.deduct(100);
    std::cout << "After deducting 100: " << myCard.getBalance() << std::endl;

    return 0;
}