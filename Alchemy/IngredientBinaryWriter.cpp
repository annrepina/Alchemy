#include "IngredientBinaryWriter.h"

IngredientBinaryWriter::IngredientBinaryWriter()
{
}

IngredientBinaryWriter::~IngredientBinaryWriter()
{
	clear();
}

void IngredientBinaryWriter::write(ofstream& stream, string filePath, Ingredient* ingredient) const
{
	BinaryWriter::write(stream, filePath, ingredient);

	// получаем и пишем название ингредиента
	string name = ingredient->getName();
	writeString(stream, name);

	// Поучаем и пишем цену за ингредиент
	int price = ingredient->getPrice();
	writeInt(stream, price);

	// Получаем и пишем кол-во ингредиентов
	int number = ingredient->getNumber();
	writeInt(stream, number);

	// Получаем кол-во эффектов и пишем его
	int numberOfEffects = ingredient->getNumberOfEffects();
	writeInt(stream, numberOfEffects);

	// получаем итераторы
	auto beginIter = ingredient->getBeginIteratorOfEffectsId();
	auto endIter = ingredient->getEndIteratorOfEffectsId();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// получаем ключ (id ингредиента) и пишем
		int key = i->first;
		writeInt(stream, key);

		// Получаем будеву, отвечающую за позитивность
		bool isPositive = i->second;
		writeBool(stream, isPositive);
	}
}

void IngredientBinaryWriter::clear()
{
}
