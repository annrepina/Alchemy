#include "Potion.h"

Potion::Potion()
{
	this->effectId = 0;
	this->number = 0;
	this->price = 0;
	this->power = 0;
}

Potion::~Potion()
{
}

void Potion::setEffectId(int id)
{
	this->effectId = id;
}

void Potion::setPrice(int price)
{
	this->price = price;
}

void Potion::setNumber(int number)
{
	this->number = number;
}

void Potion::setPower(int power)
{
	this->power = power;
}

int Potion::getNumber()
{
	return this->number;
}

int Potion::getEffectId()
{
	return this->effectId;
}

int Potion::getPower()
{
	return this->power;
}

int Potion::getPrice()
{
	return this->price;
}

void Potion::increaseNumber()
{
	++this->number;
}

void Potion::decreaseNumber(int number)
{
	this->number -= number;
}
