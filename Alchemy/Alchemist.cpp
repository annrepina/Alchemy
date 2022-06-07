#include "Alchemist.h"

Alchemist::Alchemist()
{
	this->name = "";
	this->alchemistLevel = START_LEVEL;
	this->salesmanLevel = START_LEVEL;
	this->�apital = START_UP_CAPITAL;
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
	return this->�apital;
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

void Alchemist::increaseCapital(int value)
{
	this->�apital += value;
}

void Alchemist::print()
{
	cout << "�������: " << this->name << endl
		<< "������� ��������: " << this->alchemistLevel << endl
		<< "������� ��������: " << this->salesmanLevel << endl
		<< "������: " << this->�apital << endl;
}
