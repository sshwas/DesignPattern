#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//1 Add a Japanese factory and Japanese apples and bananas (add a product family)
// Add to the product family, in line with opening and closing

//2 Add a product category, Yali (add a product grade structure)
// Add to the product level organization does not meet the opening and closing

//3 consider 1, 2 are all in line with the principle of opening and closing

class Fruit
{
public:
	virtual void getName() = 0;
};

class USAApple :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am an American apple" << endl;
	}
};

class USABanana :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a banana in the United States" << endl;
	}
};

class USAPear :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a pear of the United States" << endl;
	}
};

class ChinaApple :public Fruit
{
public:
	virtual void getName()
	{
		cout << "I am an apple in China" << endl;
	}
};

class ChinaBanana :public Fruit
{
public:
	virtual void getName()
	{
		cout << "I am a Chinese banana" << endl;
	}
};

class ChinaPear :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a Chinese pear" << endl;
	}
};

//The top one is an abstract factory, which is produced for the product family.
class AbstractFactory 
{
public:
	virtual Fruit *createApple() = 0;
	virtual Fruit *createBanana() = 0;
	//Add a pear pear generator
	virtual Fruit* createPear() = 0;
};

//The specific factory in the United States
class USAFactory :public AbstractFactory
{
public:
	virtual Fruit *createApple()
	{
		return new USAApple;
	}

	virtual Fruit *createBanana()
	{
		return new USABanana;
	}

	//Add a US producer
	virtual Fruit * createPear()
	{
		return new USAPear;
	}
};

//Chinese factory
class ChinaFactory :public AbstractFactory
{
public:
	virtual Fruit *createApple()
	{
		return new ChinaApple;
	}

	virtual Fruit *createBanana() 
	{
		return new ChinaBanana;
	}

	//Add a producer
	virtual Fruit * createPear() 
	{
		return new ChinaPear;
	}
};

//Add a Japanese product family, factory, and specific products to meet the opening and closing principle
class JapanApple :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am an apple in Japan" << endl;
	}
};

class JapanBanana :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a Japanese banana" << endl;
	}
};

class JapanPear :public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a Japanese pear" << endl;
	}
};


class JapanFactory :public AbstractFactory
{
public:
	virtual Fruit *createApple()
	{
		return new JapanApple;
	}

	virtual Fruit *createBanana()
	{
		return new JapanBanana;
	}

	virtual Fruit * createPear()
	{
		return new JapanPear;
	}
};

int main(void)
{
	//I want an American banana
	//1 to a US factory
	AbstractFactory * usaF = new USAFactory;

	//2 to a banana
	Fruit *usaBanana = usaF->createBanana();

	usaBanana->getName();

	//I want a Chinese apple
	AbstractFactory *chinaF = new ChinaFactory;
	Fruit *chinaApple = chinaF->createApple();

	chinaApple->getName();

	return 0;
}