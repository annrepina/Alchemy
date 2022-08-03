#include "Potion.h"

Potion::Potion()
{
	this->effectId = 0;
	//this->name = "";
	this->number = 0;
	this->price = 0;
	this->power = 0;
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

//Potion::Potion(Ingredient* ingredient1, Ingredient* ingredient2)
//{
//	// результат смешения ингредиентов
//	bool res = hasEffectsMatching(ingredient1, ingredient2);
//
//	// если совпадения нет
//	if (!res)
//	{
//		this->id = 0;
//		this->number = 0;
//		this->price = 0;
//	}
//}

//bool Potion::hasEffectsMatching(Ingredient* ingredient1, Ingredient* ingredient2)
//{
//	// результат смешения ингредиентов
//	bool res = false;
//
//	// id эффекта, который совпал
//	int effectId;
//
//	// Итератор на начало map с id эффектов первого ингредиента
//	auto firstBeginIter = ingredient1->getBeginIteratorOfEffectsId();
//	// Итератор на конец map с id эффектов первого ингредиента
//	auto firstEndIter = ingredient1->getEndIteratorOfEffectsId();
//
//	// Итератор на начало map с id эффектов второго ингредиента
//	auto secondBeginIter = ingredient2->getBeginIteratorOfEffectsId();
//	// Итератор на конец map с id эффектов второго ингредиента
//	auto secondEndIter = ingredient2->getEndIteratorOfEffectsId();
//
//	// в цикле проверяем эффекты на совпадение
//	for (auto i = firstBeginIter; i != firstEndIter; ++i)
//	{
//		for (auto j = secondBeginIter; j != secondEndIter; ++j)
//		{
//			if (i->first == j->first)
//			{
//				res = true;
//
//				this->id = i->first;
//				this->number = 1;
//				this->price = ingredient1->getPrice() + ingredient2->getPrice();
//
//				break;
//			}
//		}
//
//		if (res)
//			break;
//	}
//
//	return res;
//
//}
