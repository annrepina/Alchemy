#include "Alchemist.h"

Alchemist::Alchemist()
{
	this->name = "";
	this->alchemistLevel = START_LEVEL;
	this->salesmanLevel = START_LEVEL;
	this->сapital = START_UP_CAPITAL;
}

void Alchemist::setName(string name)
{
	this->name = name;
}

void Alchemist::setAlchemistLevel(int alchemistLevel)
{
	this->alchemistLevel = alchemistLevel;
}

void Alchemist::setSalesmanLevel(int salesmanLevel)
{
	this->salesmanLevel = salesmanLevel;
}

string Alchemist::getName()
{
	return this->name;
}

void Alchemist::increaseAlchemistLevel()
{
	// увеличиваем на 1
	++this->alchemistLevel;
}

void Alchemist::increaseSalesmanLevel()
{
	// увеличиваем на 1
	++this->salesmanLevel;
}

void Alchemist::increaseCapital(int value)
{
	this->сapital += value;
}

void Alchemist::print()
{
	cout << "Алхимик: " << this->name << endl
		<< "Уровень алхимика: " << this->alchemistLevel << endl
		<< "Уровень продавца: " << this->salesmanLevel << endl
		<< "Золото: " << this->сapital << endl;
}
