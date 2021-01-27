#include <cstdio>

//-------------- encapsulating behavior --------------//
class FlyBehavior
{
public:
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
	virtual void fly()
	{
		printf("I'm Flying!!\n");
	}
};

class FlyNoWay : public FlyBehavior
{
public:
	virtual void fly()
	{
		printf("I can't fly\n");
	}
};

//-------------- encapsulating behavior --------------//
class QuackBehavior
{
public:
	virtual void quack() = 0;
};

class Quack : public QuackBehavior
{
public:
	virtual void quack()
	{
		printf("Quack!!\n");
	}
};

class MuteQuack : public QuackBehavior
{
public:
	virtual void quack()
	{
		printf("<< silence >>\n");
	}
};

class SQuack : public QuackBehavior
{
public:
	virtual void quack()
	{
		printf("Squack\n");
	}
};

//-------------- Client --------------//
class Duck
{
protected:
	FlyBehavior* flyBehavior;
	QuackBehavior* quackBehavior;

public:
	Duck() {};
	~Duck() {};

	virtual void display() = 0;

	void setFlyBehavior(FlyBehavior* pFlyBehavior)
	{
		flyBehavior = pFlyBehavior;
	}

	void setQuackBehavior(QuackBehavior* pQuackBehavior)
	{
		quackBehavior = pQuackBehavior;
	}

	void performFly()
	{
		flyBehavior->fly();			// delegation
	}

	void performQuack()
	{
		quackBehavior->quack();		// delegation
	}

	void swim()
	{
		printf("All ducks float, even decoys!\n");
	}
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
	{
		quackBehavior = new MuteQuack();
		flyBehavior = new FlyWithWings();
	};

	~MallardDuck() {};

	virtual void display()
	{
		printf("I'm a real Mallard Duck!\n");
	}
};

//------------------------------------------------------//

int main()
{
	Duck* mallard = new MallardDuck();

	mallard->performQuack();
	mallard->performFly();

	QuackBehavior* quack1 = new SQuack();
	FlyBehavior* fly1 = new FlyNoWay();

	mallard->setQuackBehavior(quack1);
	mallard->setFlyBehavior(fly1);

	mallard->performQuack();
	mallard->performFly();

	mallard->display();

	return 0;
}
