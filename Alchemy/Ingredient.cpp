#include "Ingredient.h"
#include <iostream>

//int Ingredient::counter = 0;

Ingredient::Ingredient()
{
	//++counter;
	//this->id = counter;
	this->name = "";
	this->price = 0;
	this->number = 0;
	//this->effectsId.shrink_to_fit(NUMBER_OF_EFFECTS);
	//this->effectsId.reserve(NUMBER_OF_EFFECTS);
}

Ingredient::~Ingredient()
{

}

void Ingredient::print()
{
	cout << this->name << ' ' << this->price << ' ';
}

int Ingredient::getEffectId(int number)
{
	if (NUMBER_OF_EFFECTS > number)
	{
		return this->effectsId[number];
	}

	return 0;
}

string Ingredient::getName()
{
	return this->name;
}

int Ingredient::getNumber()
{
	return this->number;
}

void Ingredient::setName(string name)
{
	this->name = name;
}

void Ingredient::setPrice(float price)
{
	this->price = price;
}

void Ingredient::addEffect(int effectId)
{
	// Если размер вектора меньше двух, то добавляем элемент
	if (NUMBER_OF_EFFECTS > this->effectsId.size())
		this->effectsId.emplace(effectId, false);

	else
		return;
}

