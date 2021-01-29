#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class Iterator
{
public:
	Iterator() {}
	virtual ~Iterator() {}
	virtual bool hasNext() = 0;
	virtual T* next() = 0;
};

class MenuItem
{
private:
	string name;
	string description;
	bool vegetarian;
	float price;

public:
	MenuItem() {}
	~MenuItem();

	MenuItem(string name, string description, bool vegetarian, float price)
	{
		this->name = name;
		this->description = description;
		this->vegetarian = vegetarian;
		this->price = price;
	}

	string getName()
	{
		return name;
	}

	string getDescription()
	{
		return description;
	}

	float getPrice()
	{
		return price;
	}

	bool isVegetarian()
	{
		return vegetarian;
	}
};

class DinerMenuIterator : public Iterator<MenuItem>
{
private:
	MenuItem** items;
	int position;

public:
	DinerMenuIterator(MenuItem** _items) :items(_items), position(0) {}

	MenuItem* next()
	{
		MenuItem* menuItem = items[position];
		position++;
		return menuItem;
	}

	bool hasNext()
	{
		if (items[position] == 0)
			return false;
		else
			return true;
	}

	~DinerMenuIterator() {}
};

class PancakeHouseMenuIterator : public Iterator<MenuItem>
{
private:
	vector<MenuItem*> items;
	int position;
public:
	PancakeHouseMenuIterator(vector<MenuItem*> _items) :items(_items), position(0) {}
	MenuItem* next()
	{
		MenuItem* menuItem = items[position];
		position++;
		return menuItem;
	}

	bool hasNext()
	{
		if (position >= items.size())
			return false;
		else
			return true;
	}
	~PancakeHouseMenuIterator() {}
};

class Menu
{
public:
	Menu() {}
	virtual ~Menu() {}
	virtual Iterator<MenuItem>* createIterator() = 0;
};

class DinerMenu : public Menu
{
private:
	static const int MAX_ITEMS = 6;
	int numberOfItems;
	MenuItem** menuItems;

public:
	DinerMenu() : numberOfItems(0)
	{
		menuItems = new MenuItem*[MAX_ITEMS + 1];

		// Initialize to 0
		for (int i = 0; i <= MAX_ITEMS; ++i)
		{
			menuItems[i] = 0; //hasNext() will not go wrong
		}

		addItem("Vegtarian BLT", "(Fakin) Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on while wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day,with a side of potato aalad", false, 3.29);
		addItem("Hotdog", "A hot dog,with saurkraut, relish, onions, topped with cheese", false, 3.05);
		addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
		addItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89);
	}
	~DinerMenu() {}

	void addItem(string name, string description, bool vevetarian, float price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vevetarian, price);

		if (numberOfItems >= MAX_ITEMS)
		{
			cerr << "Sorry,menu id full! Can't add item to menu" << endl;
		}
		else
		{
			menuItems[numberOfItems] = menuItem;
			numberOfItems++;
		}
	}

	MenuItem** getMenuItems()
	{
		return menuItems;
	}

	Iterator<MenuItem>* createIterator()
	{
		Iterator<MenuItem>* it = new DinerMenuIterator(menuItems);
		return it;
	}
};

class PancakeHouseMenu
{
private:
	vector<MenuItem*> menuItems;

public:
	PancakeHouseMenu() 
	{
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancake with fried eggs£¬ sausage", false, 2.99);
		addItem("Blueberry Pancake", "Pancake made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Waffles, with your cchoice of blueberries or strawberries", true, 3.59);
	}
	~PancakeHouseMenu() {}

	void addItem(string name, string description, bool vegetarian, float price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}

	vector<MenuItem*> getMemeItems()
	{
		return menuItems;
	}

	Iterator<MenuItem>* createIterator()
	{
		Iterator<MenuItem>* it = new PancakeHouseMenuIterator(menuItems);
		return it;
	}
};

class Waitress 
{
	PancakeHouseMenu* _pancakeHouseMenu;
	DinerMenu* _dinerMenu;

	Waitress(const Waitress&); // Disable copy constructor
	void operator = (const Waitress&); // Disable assignment operator

	void printMenu(Iterator<MenuItem>* iterator)
	{
		while (iterator->hasNext()) 
		{
			MenuItem* menuItem = dynamic_cast< MenuItem* >(iterator->next());
			cout << menuItem->getName() << ", ";
			cout << menuItem->getPrice() << " -- ";
			cout << menuItem->getDescription() << endl;
		}
	}

	void printVegetarianMenu(Iterator<MenuItem>* iterator)
	{
		while (iterator->hasNext()) 
		{
			MenuItem* menuItem = dynamic_cast< MenuItem* >(iterator->next());
			if (menuItem->isVegetarian()) 
			{
				cout << menuItem->getName() << ", ";
				cout << menuItem->getPrice() << " -- ";
				cout << menuItem->getDescription() << endl;
			}
		}
	}

	bool isVegetarian(string name, Iterator<MenuItem>* iterator)
	{
		while (iterator->hasNext()) 
		{
			MenuItem* menuItem = dynamic_cast< MenuItem* >(iterator->next());
			if (menuItem->getName().compare(name) == 0) 
			{
				if (menuItem->isVegetarian()) 
				{
					return true;
				}
			}
		}
		return false;
	}

public:
	Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu) :
		_pancakeHouseMenu(pancakeHouseMenu), _dinerMenu(dinerMenu)
	{
	}

	void printMenu()
	{
		Iterator<MenuItem>* pancakeIterator = _pancakeHouseMenu->createIterator();
		Iterator<MenuItem>* dinerIterator = _dinerMenu->createIterator();

		cout << "MENU\n----\nBREAKFAST" << endl;
		printMenu(pancakeIterator);
		cout << "\nLUNCH" << endl;
		printMenu(dinerIterator);
	}

	void printVegetarianMenu()
	{
		printVegetarianMenu(_pancakeHouseMenu->createIterator());
		printVegetarianMenu(_dinerMenu->createIterator());
	}

	bool isItemVegetarian(string name)
	{
		Iterator<MenuItem>* breakfastIterator
			= _pancakeHouseMenu->createIterator();
		if (isVegetarian(name, breakfastIterator)) 
		{
			return true;
		}
		Iterator<MenuItem>* dinnerIterator = _dinerMenu->createIterator();
		if (isVegetarian(name, dinnerIterator)) 
		{
			return true;
		}
		return false;
	}
};

int main()
{
	PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
	DinerMenu* dinerMenu = new DinerMenu();

	Waitress* waitress = new Waitress(pancakeHouseMenu, dinerMenu);

	waitress->printMenu();

	delete waitress;
	delete dinerMenu;
	delete pancakeHouseMenu;
	return 0;
}
