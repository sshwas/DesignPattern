#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MenuComponent
{
public:
	virtual ~MenuComponent() { };

	// placeholder for some pure virtual functions or exception handling functions
	virtual void addChild(MenuComponent* child)
	{
		cout << "addChild exception" << endl;
	};

	virtual void removeChild(MenuComponent* child)
	{
		cout << "removeChild exception" << endl;
	};

	virtual MenuComponent* getChild(int position)
	{
		cout << "getChild exception" << endl;
		return reinterpret_cast<MenuComponent*>(0);
	};

	virtual string getName()
	{
		return "getName exception";
	};

	virtual string getDescription()
	{
		return "getDescription exception";
	};

	virtual int getPrice()
	{
		cout << "getPrice exception" << endl;
		return 0;
	}

	virtual bool isVegetarian()
	{
		cout << "isVegetarian exception" << endl;
		return false;
	}

	virtual void print()
	{
		cout << "getNumberOfMenuItems exception" << endl;
	}
};

class Menu : public MenuComponent
{

public:
	Menu(string name, string description)
	{
		this->name = name;
		this->description = description;
	};

	// placeholder for declaration of the pure virtual functions from the interface
	void addChild(MenuComponent* child)
	{
		childs_.push_back(child);
	};

	void removeChild(MenuComponent* child)
	{
		int pos = 0;
		while (pos < childs_.size())
		{
			MenuComponent* MC = childs_[pos];
			if (MC->getName() == child->getName() && MC->getDescription() == child->getDescription())
			{
				MC->print();
				break;
			}
			pos++;
		}
	};

	MenuComponent* getChild(int position)
	{
		return childs_[position];
	};

	void print()
	{
		int pos = 0;
		while (pos < childs_.size())
		{
			MenuComponent* MC = childs_[pos];
			MC->print();
			pos++;
		}
	}

private:
	// placeholder for member variables for the implementation of the pure virtual functions
	string name;
	string description;

	vector<MenuComponent*> childs_;
};

class MenuItem : public MenuComponent
{
public:
	MenuItem(string name, string description, bool vegetarian, int price)
	{
		this->name = name;
		this->description = description;
		this->vegetarian = vegetarian;
		this->price = price;
	}

	// placeholder for declaration of the pure virtual functions from the interface
	string getName()
	{
		return name;
	}
	
	string getDescription()
	{
		return name;
	}

	int getPrice()
	{
		return price;
	}

	bool isVegetarian()
	{
		return vegetarian;
	}

	void print()
	{
		cout << endl << " " << name;
		if (vegetarian)
			cout << "(v)";
		cout << ", $" << price << endl;
		cout << "  --" + description << endl;
	}

private:
	// placeholder for member variables for the implementation of the pure virtual 
	string name;
	string description;
	bool vegetarian;
	int price;
};

class Waitress
{
public :
	Waitress(MenuComponent* allMenus)
	{
		this->allMenus = allMenus;
	}

	void printMenus()
	{
		allMenus->print();
	}

private:
	MenuComponent* allMenus;
};

int main()
{
	// mid-level menu
	MenuComponent* pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
	MenuComponent* dinerMenu = new Menu("DINER MENU", "Lunch");
	MenuComponent* cafeMenu = new Menu("CAFE MENU", "Dinner");

	// adding mid-level menus to root-level menu
	MenuComponent* allMenus = new Menu("ALL MENUS", "All menus combined");
	allMenus->addChild(pancakeHouseMenu);
	allMenus->addChild(dinerMenu);
	allMenus->addChild(cafeMenu);

	// adding bottom-level menu to mid-level menu
	MenuComponent* dessertMenu = new Menu("DESSERT MENUS", "Dessert of course!");
	dinerMenu->addChild(dessertMenu);

	pancakeHouseMenu->addChild(new MenuItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 3));
	pancakeHouseMenu->addChild(new MenuItem("Regular Pancake Breakfast", "Pancakes with fried eggs, and sausage", false, 2));

	Waitress* waitress = new Waitress(allMenus);
	waitress->printMenus();

	return 0;
}