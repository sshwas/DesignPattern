#include <cstdio>

//-------------- encapsulating behavior --------------//
class WeaponBehavior
{
public:
	virtual void useWeapon() = 0;
};

class AxeBehavior : public WeaponBehavior
{
public:
	virtual void useWeapon()
	{
		printf("Axe !!\n");
	}
};

class SwordBehavior : public WeaponBehavior
{
public:
	virtual void useWeapon()
	{
		printf("Sword !!\n");
	}
};

class KnifeBehavior : public WeaponBehavior
{
public:
	virtual void useWeapon()
	{
		printf("Knife !!\n");
	}
};

class BowAndArrowBehavior : public WeaponBehavior
{
public:
	virtual void useWeapon()
	{
		printf("Bow And Arrow !!\n");
	}
};

//-------------- Client --------------//
class Character
{
protected:
	WeaponBehavior* weaponBehavior;

public:
	Character() {};
	~Character() {};

	virtual void display() = 0;

	void setWeapon(WeaponBehavior* pWeaponBehavior)
	{
		weaponBehavior = pWeaponBehavior;
	}

	void fight()
	{
		weaponBehavior->useWeapon();
	}
};

class King : public Character
{
public:
	King()
	{
		weaponBehavior = new AxeBehavior();
	};

	~King() {};

	virtual void display()
	{
		printf("I'm a King!\n");
	}
};

class Queen : public Character
{
public:
	Queen()
	{
		weaponBehavior = new KnifeBehavior();
	};

	~Queen() {};

	virtual void display()
	{
		printf("I'm a Queen!\n");
	}
};

class Prince : public Character
{
public:
	Prince()
	{
		weaponBehavior = new BowAndArrowBehavior();
	};

	~Prince() {};

	virtual void display()
	{
		printf("I'm a Prince!\n");
	}
};

class Knight : public Character
{
public:
	Knight()
	{
		weaponBehavior = new SwordBehavior();
	};

	~Knight() {};

	virtual void display()
	{
		printf("I'm a Knight!\n");
	}
};

//------------------------------------------------------//

int main()
{
	Character* ch = new King();
	ch->display();
	ch->fight();

	ch = new Queen();
	ch->display();
	ch->fight();

	ch = new Prince();
	ch->display();
	ch->fight();

	ch = new Knight();
	ch->display();
	ch->fight();

	WeaponBehavior* pKnife = new KnifeBehavior();
	ch->setWeapon(pKnife);
	ch->display();
	ch->fight();

	return 0;
}
