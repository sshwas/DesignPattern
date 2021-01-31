#include <iostream>
using namespace std;

enum STATE { NO_QUARTER, SOLD_OUT, HAS_QUARTER, SOLD, WINNER };

class GumballMachine;

class State
{
public:
	State(GumballMachine* gumballMachine)
	{
		m_gumballMachine = gumballMachine;
	}
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;

protected:
	GumballMachine* m_gumballMachine;
};

class NoQuarterState : public State
{
public:
	NoQuarterState(GumballMachine* g) :State(g) {}
	
	void insertQuarter() override
	{
		cout << "You inserted a quarter" << endl;
		m_gumballMachine->setState(HAS_QUARTER);
	}

	void ejectQuarter() override
	{
		cout << "You haven't inserted a quarter" << endl;
	}

	void turnCrank() override
	{
		cout << "You turned, but there's no quarter" << endl;
	}

	void dispense() override
	{
		cout << "You need to pay first" << endl;
	}
};

class SoldOutState : public State
{
public:
	SoldOutState(GumballMachine* g) :State(g) {}

	void insertQuarter() override
	{
		cout << "No need to insert a quarter, the machine is sold out" << endl;
		m_gumballMachine->setState(HAS_QUARTER);
	}

	void ejectQuarter() override
	{
		cout << "You can't eject, you haven't inserted a quarter yet" << endl;
	}

	void turnCrank() override
	{
		cout << "You turned, but there are no gumballs" << endl;
	}

	void dispense() override
	{
		cout << "No gumball dispensed" << endl;
	}
};

class SoldState : public State
{
public:
	SoldState(GumballMachine* g) :State(g) {}

	void insertQuarter() override
	{
		cout << "Please wait, we're already giving you a gumball" << endl;
		m_gumballMachine->setState(HAS_QUARTER);
	}

	void ejectQuarter() override
	{
		cout << "Sorry, you already turned the crank" << endl;
	}

	void turnCrank() override
	{
		cout << "Turning twice doesn't get you another gumball!" << endl;
	}

	void dispense() override
	{
		m_gumballMachine->releaseBall();
		if (m_gumballMachine->isSoldOut())
		{
			m_gumballMachine->setState(SOLD_OUT);
		}
		else
		{
			m_gumballMachine->setState(NO_QUARTER);
		}
	}
};

class HasQuarterState : public State
{
public:
	HasQuarterState(GumballMachine* g) :State(g) {}

	void insertQuarter() override
	{
		cout << "You can't insert another quarter" << endl;
	}

	void ejectQuarter() override
	{
		cout << "Quarter returned" << endl;
		m_gumballMachine->setState(NO_QUARTER);
	}

	void turnCrank() override
	{
		cout << "You turned..." << endl;
		if (rand() % 10 == 0)
		{
			m_gumballMachine->setState(WINNER);
		}
		else
		{
			m_gumballMachine->setState(SOLD);
		}
	}

	void dispense() override
	{
		cout << "No gumball dispensed" << endl;
	}
};

class WinnerState : public State
{
public:
	WinnerState(GumballMachine* g) :State(g) {}

	void insertQuarter() override
	{
		cout << "Please wait, we're already giving you a Gumball" << endl;
	}

	void ejectQuarter() override
	{
		cout << "Please wait, we're already giving you a Gumball" << endl;
	}

	void turnCrank() override
	{
		cout << "Turning again doesn't get you another gumball!" << endl;
		m_gumballMachine->releaseBall();
	}

	void dispense() override
	{
		cout << "YOU'RE A WINNER! You get two gumballs for your quarter" << endl;
		
		m_gumballMachine->releaseBall();

		if (m_gumballMachine->isSoldOut())
		{
			m_gumballMachine->setState(SOLD_OUT);
		}
		else
		{
			m_gumballMachine->releaseBall();
			if (m_gumballMachine->isSoldOut())
			{
				m_gumballMachine->setState(SOLD_OUT);
			}
			else
			{
				m_gumballMachine->setState(NO_QUARTER);
			}
		}
	}
};

class GumballMachine
{
public:	
	GumballMachine::GumballMachine(int numberGumballs)
		: m_count(numberGumballs),
		m_soldOutState(this),
		m_noQuarterState(this),
		m_hasQuarterState(this),
		m_soldState(this),
		m_winnerState(this)
	{
		m_state = &m_noQuarterState;
		if (numberGumballs > 0)
		{
			m_state = &m_noQuarterState;
		}
	}

	void setState(enum STATE state)
	{
		switch (state)
		{
		case NO_QUARTER:
			m_state = &m_noQuarterState;
			break;
		case SOLD_OUT:
			m_state = &m_soldOutState;
			break;
		case HAS_QUARTER:
			m_state = &m_hasQuarterState;
			break;
		case SOLD:
			m_state = &m_soldState;
			break;
		case WINNER:
			m_state = &m_winnerState;
			break;
		default:
			break;
		}
	}

	void releaseBall()
	{
		cout << "A gumball comes rolling out the slot..." << endl;
		if (m_count != 0)
		{
			m_count = m_count - 1;
		}
	}

	bool isSoldOut() { return m_count == 0; }

	void refill(int count)
	{
		m_count = count;
		m_state = &m_noQuarterState;
	}

	void insertQuarter()
	{
		m_state->insertQuarter();
	}

	void ejectQuarter()
	{
		m_state->ejectQuarter();
	}

	void turnCrank()
	{
		m_state->turnCrank();
		m_state->dispense();
	}

private:
	int m_count;
	State* m_state;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	SoldState m_soldState;
	WinnerState m_winnerState;
};

int main()
{
	GumballMachine gumballMachine(5);

	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();

	gumballMachine.insertQuarter();
	gumballMachine.ejectQuarter();
	gumballMachine.turnCrank();

	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.ejectQuarter();

	gumballMachine.insertQuarter();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();
	gumballMachine.insertQuarter();
	gumballMachine.turnCrank();

	return 0;
}