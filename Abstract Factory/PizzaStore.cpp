#include <iostream>
#include <string>
using namespace std;

// Abstract Factory Pattern

class PizzaIngredientFactory;

// Product
class Pizza
{
public:
	string name;
	string dough;
	string sauce;

	virtual void prepare() = 0;

	void setName(string name)
	{
		this->name = name;
	}

	void bake()
	{
		cout << "bake for 25 mins at 350..." << endl;
	}

	void cut()
	{
		cout << "Cutting the pizza into diagonal slices..." << endl;
	}

	void box()
	{
		cout << "Place pizza in official PizzaStore box..." << endl;
	}
};

// Concrete Product
class CheesePizza : public Pizza
{
public:
	PizzaIngredientFactory* ingredientFactory;

	CheesePizza(PizzaIngredientFactory* Factory)
	{
		this->ingredientFactory = Factory;
	}

	void prepare()
	{
		cout << name << endl;
		cout << ingredientFactory->createDough() << endl;
		cout << ingredientFactory->createSauce() << endl;
	}
};

class GreekPizza : public Pizza
{
public:
	PizzaIngredientFactory* ingredientFactory;

	GreekPizza(PizzaIngredientFactory* Factory)
	{
		this->ingredientFactory = Factory;
	}

	void prepare()
	{
		cout << name << endl;
		cout << ingredientFactory->createDough() << endl;
	}
};

class PizzaIngredientFactory
{
public:
	virtual string createDough() = 0;
	virtual string createSauce() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	string createDough()
	{
		return "NY Dough";
	}

	string createSauce()
	{
		return "NY Sauce";
	}
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	string createDough()
	{
		return "Chicago Dough";
	}

	string createSauce()
	{
		return "Chicago Sauce";
	}
};

// Creator
class PizzaStore
{
public:
	Pizza* pizza;

	Pizza* orderPizza(string type)
	{
		//orderPizza uses the factory to complete the creation by passing in the type
		pizza = createPizza(type);

		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
		cout << endl;

		return pizza;
	}

protected:
	virtual Pizza* createPizza(string type) = 0;
};

// Concrete Creator
class NYPizzaStore : public PizzaStore
{
public:
	Pizza* pizza;
	PizzaIngredientFactory* ingredientFactory;

	Pizza* createPizza(string type)
	{
		ingredientFactory = new NYPizzaIngredientFactory();

		if (type.compare("cheese") == 0)
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("NY Style Cheese Pizza");
		}
		else if (type.compare("greek") == 0)
		{
			pizza = new GreekPizza(ingredientFactory);
			pizza->setName("NY Style Greek Pizza");
		}
		return pizza;
	}
};

// Concrete Creator
class ChicagoPizzaStore : public PizzaStore
{
public:
	Pizza* pizza;
	PizzaIngredientFactory* ingredientFactory;

	Pizza* createPizza(string type)
	{
		ingredientFactory = new ChicagoPizzaIngredientFactory();

		if (type.compare("cheese") == 0)
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("Chicago Style Cheese Pizza");
		}
		else if (type.compare("greek") == 0)
		{
			pizza = new GreekPizza(ingredientFactory);
			pizza->setName("Chicago Style Greek Pizza");
		}
		return pizza;
	}
};

int main()
{
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();

	Pizza* pizza = nyStore->orderPizza("cheese");
	pizza = nyStore->orderPizza("greek");
	pizza = chicagoStore->orderPizza("cheese");
	pizza = chicagoStore->orderPizza("greek");

	return 0;
}