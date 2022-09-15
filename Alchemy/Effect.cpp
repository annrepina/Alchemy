#include "Effect.h"
#include <iostream>

Effect::Effect()
{
	name = "";
	isPositive = false;
}

Effect::Effect(string name, bool isPositive)
{
	this->name = name;
	this->isPositive = isPositive;
}

Effect::~Effect()
{

}

void Effect::setName(string name)
{
	this->name = name;
}

void Effect::setIsPositive(bool isPositive)
{
	this->isPositive = isPositive;
}

string Effect::getName()
{
	return this->name;
}

bool Effect::getIsPositive()
{
	return isPositive;
}

void Effect::print()
{
	cout << this->name << ' ' << this->isPositive;
}