#include <iostream>
using namespace std;

class Duck
{
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class MallardDuck : public Duck
{
public:
	void quack()
	{
		cout << "Quack" << endl;
	}

	void fly()
	{
		cout << "I am flying" << endl;
	}
};

class Turkey
{
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
public:
	void gobble()
	{
		cout << "Gobble Gobble" << endl;
	}

	void fly()
	{
		cout << "I am flying a short distance" << endl;
	}
};

class TurkeyAdapter : public Duck
{
public:
	Turkey* turkey;

	TurkeyAdapter(Turkey* turkey)
	{
		this->turkey = turkey;
	}

	void quack()
	{
		turkey->gobble();
	}

	void fly()
	{
		for (int i = 0; i < 5; i++)
		{
			turkey->fly();
		}
	}
};

int main()
{
	MallardDuck* duck = new MallardDuck();
	WildTurkey* turkey = new WildTurkey();

	Duck* turkeyAdapter = new TurkeyAdapter(turkey);

	cout << "The Turkey says..." << endl;

	turkey->gobble();
	turkey->fly();

	cout << "The Duck says..." << endl;

	duck->quack();
	duck->fly();

	cout << "The TurkeyAdapter says..." << endl;

	turkeyAdapter->quack();
	turkeyAdapter->fly();

	return 0;
}