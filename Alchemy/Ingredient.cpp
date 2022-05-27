#include "Ingredient.h"

int Ingredient::counter = 0;

Ingredient::Ingredient()
{
	++counter;
	this->id = counter;
	this->name = "";
	this->price = 0.f;
	this->effectsId.reserve(NUMBER_OF_EFFECTS);
}

Ingredient::~Ingredient()
{

}

void Ingredient::setName(string name)
{
	this->name = name;
}

void Ingredient::setPrice(float price)
{
	this->price = price;
}

//void Ingredient::setId(int id)
//{
//	this->id = id;
//}

void Ingredient::addEffect(int effectId)
{
	// Если размер вектора меньше двух, то добавляем элемент
	if (NUMBER_OF_EFFECTS < this->effectsId.size())
		this->effectsId.push_back(effectId);

	else
		return;
}

//void Ingredient::clear()
//{
//	//for (auto effect : effectsId)
//	//{
//	//	delete effect;
//	//	effect = nullptr;
//	//}
//}

