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

bool Ingredient::getEffectIsKnown(int number)
{
	if (NUMBER_OF_EFFECTS > number)
	{
		int id = this->effectsId[number];
		return id/*this->effectsId[number]*/;
	}

	return 0;
}

map<int, bool>::iterator Ingredient::getBeginIteratorOfEffectsId()
{
	// �������� �� ������ �������
	map<int, bool>::iterator iter = this->effectsId.begin();

	return iter;
}

map<int, bool>::iterator Ingredient::getEndIteratorOfEffectsId()
{
	// �������� �� ������� ����� �����
	map<int, bool>::iterator iter = this->effectsId.end();

	return iter;
}

string Ingredient::getName()
{
	return this->name;
}

int Ingredient::getNumber()
{
	return this->number;
}

int Ingredient::getPrice()
{
	return this->price;
}

void Ingredient::setName(string name)
{
	this->name = name;
}

void Ingredient::setPrice(float price)
{
	this->price = price;
}

void Ingredient::setNumber(int number)
{
	this->number = number;
}

void Ingredient::openEffect(int id)
{
	this->effectsId[id] = KNOWN;

	//this->notify(id);
}

void Ingredient::openEffectRandomly()
{
	// �������� �� ������
	auto beginIter = this->effectsId.begin();

	// �������� �� �����
	auto endIter = this->effectsId.end();

	for (auto i = beginIter; i != endIter; ++i)
	{
		if (beginIter->second == UNKNOWN)
		{
			beginIter->second = KNOWN;
			break;
		}
	}
}

void Ingredient::addEffect(int effectId)
{
	// ���� ������ ������� ������ ����, �� ��������� �������
	if (NUMBER_OF_EFFECTS > this->effectsId.size())
		this->effectsId.emplace(effectId, false);

	else
		return;
}

void Ingredient::increaseNumber(int number)
{
	this->number += number;
}

void Ingredient::decreaseNumber(int number)
{
	this->number -= number;
}

