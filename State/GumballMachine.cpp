#include <iostream>
using namespace std;

class GumballMachine; // context

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
	NoQuarterState(GumballMachine * g) :State(g) {}
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class SoldOutState :public State
{
public:
	SoldOutState(GumballMachine * g) :State(g)
	{
	}

	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class HasQuarterState : public State
{
public:
	HasQuarterState(GumballMachine * g) :State(g)
	{
	}

	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class SoldState : public State
{
public:
	SoldState(GumballMachine * g) :State(g)
	{
	}

	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};


class WinnerState : public State
{
public:
	WinnerState(GumballMachine * g) :State(g)
	{
	}

	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

void NoQuarterState::insertQuarter()
{
	cout << "You inserted a quarter" << endl;
	m_gumballMachine->setState(GumballMachine::HAS_QUARTER);
}
void NoQuarterState::ejectQuarter()
{
	cout << "You haven't inserted a quarter" << endl;
}
void NoQuarterState::turnCrank()
{
	cout << "You turned, but there's no quarter" << endl;
}
void NoQuarterState::dispense()
{
	cout << "You need to pay first" << endl;
}
////////////////////////////////////////////////////////////////////////////
void SoldOutState::insertQuarter()
{
	cout << "You can't insert a quarter, the machine is sold out" << endl;
}

void SoldOutState::ejectQuarter()
{
	cout << "You can't eject, you haven't inserted a quarter yet" << endl;
}

void SoldOutState::turnCrank()
{
	cout << "You turned, but there are no gumballs" << endl;
}

void SoldOutState::dispense()
{
	cout << "No gumball dispensed" << endl;
}

//QString SoldOutState::toString()
//{
//    return QString("sold out");
//}


///////////////////////////////////////////////
void SoldState::insertQuarter()
{
	cout << "Please wait, we're already giving you a gumball" << endl;
	m_gumballMachine->setState(GumballMachine::HAS_QUARTER);
}
void SoldState::ejectQuarter()
{
	cout << "Sorry, you already turned the crank" << endl;
}
void SoldState::turnCrank()
{
	cout << "Turning twice doesn't get you another gumball!" << endl;
}
void SoldState::dispense()
{
	m_gumballMachine->releaseBall();
	if (m_gumballMachine->isSoldOut())
	{
		m_gumballMachine->setState(GumballMachine::SOLD_OUT);
	}
	else
	{
		m_gumballMachine->setState(GumballMachine::NO_QUARTER);
	}
}
////////////////////////////////////////////////////////////////////////////
void HasQuarterState::insertQuarter()
{
	cout << "You can't insert another quarter" << endl;
}

void HasQuarterState::ejectQuarter()
{
	cout << "Quarter returned" << endl;
	m_gumballMachine->setState(GumballMachine::NO_QUARTER);
}

void HasQuarterState::turnCrank()
{
	cout << "You turned..." << endl;
	if (rand() % 10 == 0)
	{
		m_gumballMachine->setState(GumballMachine::WINNER);
	}
	else
	{
		m_gumballMachine->setState(GumballMachine::SOLD);
	}
}

void HasQuarterState::dispense()
{
	cout << "No gumball dispensed" << endl;
}
//////////////////////////////////////////////////////////////////////////////
void WinnerState::insertQuarter()
{
	cout << "Please wait, we're already giving you a Gumball" << endl;
}

void WinnerState::ejectQuarter()
{
	cout << "Please wait, we're already giving you a Gumball" << endl;
	//m_gumballMachine->setState(NO_QUARTER);
}

void WinnerState::turnCrank()
{
	cout << "Turning again doesn't get you another gumball!" << endl;
	m_gumballMachine->releaseBall();

}

void WinnerState::dispense()
{
	cout << "YOU'RE A WINNER! You get two gumballs for your quarter" << endl;
	m_gumballMachine->releaseBall();
	if (m_gumballMachine->isSoldOut())
	{
		m_gumballMachine->setState(GumballMachine::SOLD_OUT);
	}
	else
	{
		m_gumballMachine->releaseBall();
		if (m_gumballMachine->isSoldOut())
		{
			m_gumballMachine->setState(GumballMachine::SOLD_OUT);
		}
		else
		{
			m_gumballMachine->setState(GumballMachine::NO_QUARTER);
		}
	}
}

class GumballMachine
{
public:
	enum STATE { NO_QUARTER, SOLD_OUT, HAS_QUARTER, SOLD, WINNER };
	GumballMachine(int numberGumballs);
	void setState(enum STATE state);
	void releaseBall();
	bool isSoldOut() { return m_count == 0; }
	void refill(int count);
	void insertQuarter(void);
	void ejectQuarter(void);
	void turnCrank(void);

private:
	int m_count;
	State * m_state;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	SoldState m_soldState;
	WinnerState m_winnerState;
};

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


void GumballMachine::setState(enum STATE state)
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
void GumballMachine::releaseBall()
{
	cout << "A gumball comes rolling out the slot..." << endl;
	if (m_count != 0)
	{
		m_count = m_count - 1;
	}
}

void GumballMachine::refill(int count)
{
	m_count = count;
	m_state = &m_noQuarterState;
}

void GumballMachine::insertQuarter(void)
{
	m_state->insertQuarter();
}

void GumballMachine::ejectQuarter(void)
{
	m_state->ejectQuarter();
}

void GumballMachine::turnCrank(void)
{
	m_state->turnCrank();
	m_state->dispense();
}

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