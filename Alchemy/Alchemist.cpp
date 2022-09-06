#include "Alchemist.h"

Alchemist::Alchemist()
{
	this->name = "";
	this->alchemistLevel = START_LEVEL;
	this->salesmanLevel = START_LEVEL;
	this->capital = START_UP_CAPITAL;
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

void Alchemist::setCapital(int capital)
{
	this->capital = capital;
}

string Alchemist::getName()
{
	return this->name;
}

int Alchemist::getCapital()
{
	return this->capital;
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
	// ����������� �� 1
	++this->alchemistLevel;
}

void Alchemist::increaseSalesmanLevel()
{
	// ����������� �� 1
	++this->salesmanLevel;
}

void Alchemist::increaseSalesmanLevel(int number)
{
	this->salesmanLevel += number;
}

void Alchemist::increaseCapital(int value)
{
	this->capital += value;
}

void Alchemist::decreaseCapital(int value)
{
	this->capital -= value;
}

void Alchemist::print()
{
	cout << "�������: " << this->name << endl
		<< "������� ��������: " << this->alchemistLevel / LEVEL_DIVISOR << endl
		<< "������� ��������: " << this->salesmanLevel / LEVEL_DIVISOR << endl
		<< "������: " << this->capital << endl;
}
