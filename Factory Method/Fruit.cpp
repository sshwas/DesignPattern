#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//Abstract fruit class
class Fruit
{
public:
	virtual void getName() = 0;
};

class Apple :public Fruit 
{
public:
	virtual void getName() {
		cout << "I am an apple" << endl;
	}
};

class Banana :public Fruit 
{
public:
	virtual void getName() {
		cout << "I am a banana" << endl;
	}
};

//Add a pear product
class Pear : public Fruit
{
public:
	virtual void getName() 
	{
		cout << "I am a pear" << endl;
	}
};

//Abstract factory class
class AbstractFactory
{
public:
	virtual Fruit * createFruit() = 0; // abstract fruit producer
};

//Apple's factory
class AppleFactory :public AbstractFactory
{
public:
	virtual Fruit * createFruit() 
	{
		return new Apple;
	}
};

//Banana factory 
class BananaFactory : public AbstractFactory
{
public:
	virtual Fruit *createFruit() 
	{
		return new Banana;
	}
};

//Add a pear factory
class PearFactory :public AbstractFactory
{
public:
	virtual Fruit *createFruit() 
	{
		return  new Pear;
	}
};

int main(void)
{
	//1 Give me a banana factory
	AbstractFactory * bananaFactory = new BananaFactory;
	//2 Give me a fruit
	Fruit* banana = bananaFactory->createFruit(); // can only generate bananas // polymorphism
												   //Fruit *banana = new Banana;
	banana->getName(); //polymorphism

	delete bananaFactory;
	delete banana;

	AbstractFactory *appleFactory = new AppleFactory;
	Fruit* apple = appleFactory->createFruit();
	apple->getName();

	AbstractFactory *pearFactory = new PearFactory;
	Fruit* pear = pearFactory->createFruit();
	//Fruit *pear = new Pear;
	pear->getName(); //polymorphism

	return 0;
}
