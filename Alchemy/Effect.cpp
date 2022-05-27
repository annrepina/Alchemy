#include "Effect.h"
#include <iostream>

//int Effect::counter = 0;

Effect::Effect()
{
	name = "";
	isPositive = false;
	//++counter;
	//id = counter;

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

void Effect::print()
{
	cout << this->name << '\t' << this->isPositive;
}

//void Effect::setId(int id)
//{
//	this->id = id;
//}
