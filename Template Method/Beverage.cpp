// "Head First Design Pattern" C++ implementation [Template Method Pattern]

#include <iostream>

using namespace std;

class Beverage 
{
public:
	void boil_water() 
	{
		cout << "Boiling water..." << endl;
	}

	virtual void brew() {}

	void pour_into_cup() 
	{
		cout << "Pouring into cup..." << endl;
	}

	// Add seasoning
	virtual void add_condiments() {}
		
	// general algorithm -> Template Method Block (final - avoid inheritance)
	virtual void prepare_recipe() final
	{
		boil_water();
		brew();
		pour_into_cup();
		add_condiments();
	}
};

// Coffee
class Coffee : public Beverage
{
public:
	// override
	void brew() 
	{
		cout << "Coffee - brewing..." << endl;
	}

	void add_condiments() 
	{
		cout << "Coffee - adding sugar and milk" << endl;
	}
};

// Tea
class Tea : public Beverage 
{
public:
	// override
	void brew() 
	{
		cout << "Tea - brewing..." << endl;
	}

	void add_condiments() 
	{
		cout << "Tea - adding lemon..." << endl;
	}
};

int main(int argc, char const *argv[])
{
	Beverage *coffee = new Coffee();
	Beverage *tea = new Tea();

	coffee->prepare_recipe();
	cout << "-------------------" << endl;
	tea->prepare_recipe();

	return 0;
}