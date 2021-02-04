#include <iostream>
using namespace std;

#define DELETE(pointer) delete pointer; pointer=nullptr

class Abstraction // Abstract interface
{
public:
	virtual ~Abstraction() {}
	virtual void operation() = 0;

protected:
	Abstraction() {}
};

class Implement // Implement abstract interface
{
public:
	virtual ~Implement() {}
	virtual void operation() = 0;

protected:
	Implement() {}
};

class ConcreteImplementA : public Implement // Specific implementation details class A
{
public:
	virtual void operation() override
	{
		cout << "run function ConcreteImplementA::operation()!" << endl;
	}
};

class ConcreteImplementB : public Implement // Specific implementation details class B
{
public:
	virtual void operation() override
	{
		cout << "run function ConcreteImplementB::operation()!" << endl;
	}
};

class RefinedAbstraction : public Abstraction // concrete abstraction detail class
{
public:
	RefinedAbstraction(Implement* implement)
	{
		this->implement = implement;
	}
	virtual void operation() override
	{
		cout << "enter function RefinedAbstraction::operation()!" << endl;
		implement->operation();
	}

private:
	Implement* implement;
};

int main()
{
	//Abstract instance call implementation A
	Implement *implement = new ConcreteImplementA();
	Abstraction *abstraction = new RefinedAbstraction(implement);
	abstraction->operation();
	DELETE(implement);
	DELETE(abstraction);

	//Abstract instance call implementation B
	implement = new ConcreteImplementB();
	abstraction = new RefinedAbstraction(implement);
	abstraction->operation();
	DELETE(implement);
	DELETE(abstraction);

	return 0;
}
