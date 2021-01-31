#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// 0--------- abstract layer ------
class CPU
{
public:
	virtual void caculate() = 0;
};

class Card
{
public:
	virtual void display() = 0;
};

class Memory
{
public:
	virtual void storage() = 0;
};

class AbstractFactory
{
public:
	virtual CPU* createCPU() = 0;
	virtual Card* createCard() = 0;
	virtual Memory * createMem() = 0;
};

// Architecture class
class Computer
{
public:
	Computer(CPU *cpu, Card *card, Memory *mem)
	{
		this->cpu = cpu;
		this->card = card;
		this->mem = mem;
	}

	void work()
	{
		this->cpu->caculate();
		this->card->display();
		this->mem->storage();
	}

private:
	CPU *cpu;
	Card*card;
	Memory *mem;
};

// The end of the abstraction layer ------

// ----- Implementation layer -----
// intel manufacturer

class IntelCPU : public CPU
{
public:
	virtual void caculate() 
	{
		cout << "Intel CPU starts calculating..." << endl;
	}
};

class IntelCard : public Card
{
public:
	virtual void display() 
	{
		cout << "Intel card starts showing..." << endl;
	}
};

class IntelMem : public Memory
{
public:
	virtual void storage() 
	{
		cout << "Intel mem started storing..." << endl;
	}
};

class IntelFactory : public AbstractFactory
{
public:
	virtual CPU* createCPU() 
	{
		return new IntelCPU;
	}

	virtual Card* createCard() 
	{
		return new IntelCard;
	}

	virtual Memory * createMem() 
	{
		return new IntelMem;
	}
};

// NVIDIA vendor
class NvidiaCPU : public CPU
{
public:
	virtual void caculate() 
	{
		cout << "Nvidia CPU starts counting..." << endl;
	}
};

class NvidiaCard : public Card
{
public:
	virtual void display() 
	{
		cout << "Nvidia card starts showing..." << endl;
	}
};

class NvidiaMem : public Memory
{
public:
	virtual void storage() 
	{
		cout << "Nvidia mem started storing..." << endl;
	}
};

class NvidiaFacory : public AbstractFactory
{
public:
	virtual CPU* createCPU() 
	{
		return new NvidiaCPU;
	}

	virtual Card* createCard() 
	{
		return new NvidiaCard;
	}

	virtual Memory * createMem() 
	{
		return new NvidiaMem;
	}
};


// Kinston manufacturer
class KinstonCPU : public CPU
{
public:
	virtual void caculate()
	{
		cout << "Kinston CPU starts counting..." << endl;
	}
};

class KinstonCard : public Card
{
public:
	virtual void display() 
	{
		cout << "Kinston card starts showing..." << endl;
	}
};

class KinstonMem : public Memory
{
public:
	virtual void storage() 
	{
		cout << "Kinston mem started storing..." << endl;
	}
};

class KinstonFacory : public AbstractFactory
{
public:
	virtual CPU* createCPU() 
	{
		return new KinstonCPU;
	}

	virtual Card* createCard() 
	{
		return new KinstonCard;
	}

	virtual Memory * createMem() 
	{
		return new KinstonMem;
	}
};

int main(void)
{
	//1 Assembling an intel series of computers Perform a unit test on all Intel products.
	//Create an intel factory
	AbstractFactory * intelFactory = new IntelFactory;
	CPU *intelCPU = intelFactory->createCPU();
	Card *intelCard = intelFactory->createCard();
	Memory *intelMem = intelFactory->createMem();

	Computer *com1 = new Computer(intelCPU, intelCard, intelMem);
	com1->work();

	cout << " -----  " << endl;

	//2 assemble an intel cpu kinston card NVIDIA graphics card computer
	AbstractFactory *kinstonFactory = new KinstonFacory;
	Memory *kingstonMem = kinstonFactory->createMem();
	AbstractFactory *nvidiaFactory = new NvidiaFacory;
	Card *nvidiaCard = nvidiaFactory->createCard();

	Computer *com2 = new Computer(intelCPU, nvidiaCard, kingstonMem);
	com2->work();

	return 0;
}
