#include <iostream>
using namespace std;

//Define the price of each commodity
const int ESPRESSO_PRICE = 25;
const int DRAKROAST_PRICE = 20;
const int MOCHA_PRICE = 10;
const int WHIP_PRICE = 8;

class Beverage 
{
protected:
	string description;

public:
	//virtual cannot be saved here, otherwise the previous Beverage will not be found		
	virtual string getDescription() 
	{
		return description;
	}
	virtual int cost() = 0;
};

//Ingredients
class CondimentDecorator : public Beverage 
{
protected:
	Beverage *beverage; //This pointer is used to trace back the existing content
};

//Beverage *beverage is not in the constructor of the two types of coffee; that is to say, these two classes can only be used as the basis, and cannot be used as superimposed accessories.
class Espresso : public Beverage 
{
public:
	Espresso() 
	{
		description = "Espresso";
	}

	int cost() 
	{
		return ESPRESSO_PRICE;
	}
};

class DarkRoast : public Beverage 
{
public:
	DarkRoast() 
	{
		description = "DardRoast";
	}

	int cost() 
	{
		return DRAKROAST_PRICE;
	}
};

// Compared with the above two "base classes", the constructors of these two things both exist Beverage *beverage;
// (The declaration of Beverage *beverage; is derived from the inheritance of CondimentDecorator), which can be superimposed

class Mocha : public CondimentDecorator 
{
public:
	Mocha(Beverage* beverage) 
	{
		this->beverage = beverage;
	}

	string getDescription() 
	{
		return beverage->getDescription() + ",Mocha";
	}

	int cost() 
	{
		return MOCHA_PRICE + beverage->cost();
	}
};

class Whip :public CondimentDecorator 
{
public:
	Whip(Beverage* beverage) 
	{
		this->beverage = beverage;
	}

	string getDescription() 
	{
		return beverage->getDescription() + ",Whip";
	}

	int cost() 
	{
		return WHIP_PRICE + beverage->cost();
	}
};

int main() 
{
	Beverage* beverage = new DarkRoast();
	beverage = new Mocha(beverage);
	beverage = new Whip(beverage);
	
	cout << beverage->getDescription().c_str() << " $" << beverage->cost() << endl;
	
	return 0;
}

