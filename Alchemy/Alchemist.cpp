#include "Alchemist.h"

Alchemist::Alchemist()
{
	this->name = "";
	this->alchemistLevel = START_LEVEL;
	this->salesmanLevel = START_LEVEL;
	this->ñapital = START_UP_CAPITAL;
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

int Alchemist::getCapital()
{
	return this->ñapital;
}

int Alchemist::getAlchemistLevel()
{
	return this->alchemistLevel;
}

int Alchemist::getSalesmanLevel()
{
	return this->salesmanLevel;
}

void Alchemist::increaseAlchemistLevel()
{
	// óâåëè÷èâàåì íà 1
	++this->alchemistLevel;
}

void Alchemist::increaseSalesmanLevel()
{
	// óâåëè÷èâàåì íà 1
	++this->salesmanLevel;
}

void Alchemist::increaseCapital(int value)
{
	this->ñapital += value;
}

void Alchemist::decreaseCapital(int value)
{
	this->ñapital -= value;
}

void Alchemist::print()
{
	cout << "Àëõèìèê: " << this->name << endl
		<< "Óðîâåíü àëõèìèêà: " << this->alchemistLevel / LEVEL_DIVISOR << endl
		<< "Óðîâåíü ïðîäàâöà: " << this->salesmanLevel / LEVEL_DIVISOR << endl
		<< "Çîëîòî: " << this->ñapital << endl;
}
