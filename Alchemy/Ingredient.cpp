#include "Ingredient.h"
#include <iostream>

Ingredient::Ingredient()
{
	this->name = "";
	this->price = 0;
	this->number = 0;
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
	if (numberOfEffects > number)
	{
		bool id = this->effectsId[number];
		return id;
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

int Ingredient::getNumberOfEffects()
{
	return this->numberOfEffects;
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
}

void Ingredient::openEffectRandomly()
{
	// �������� �� ������
	auto beginIter = this->effectsId.begin();

	// �������� �� �����
	auto endIter = this->effectsId.end();

	for (auto i = beginIter; i != endIter; ++i)
	{
		if (i->second == UNKNOWN)
		{
			i->second = KNOWN;
			break;
		}
	}
}

void Ingredient::addEffect(int effectId)
{
	// ���� ������ ������� ������ ����, �� ��������� �������
	if (numberOfEffects > this->effectsId.size())
		this->effectsId.emplace(effectId, false);

	else
		return;
}

void Ingredient::addEffectWithCharacteristic(int effectId, bool characteristic)
{
	// ���� ������ ������� ������ ����, �� ��������� �������
	if (numberOfEffects > this->effectsId.size())
		this->effectsId.emplace(effectId, characteristic);

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