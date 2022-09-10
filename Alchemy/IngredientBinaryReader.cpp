#include "IngredientBinaryReader.h"

IngredientBinaryReader::IngredientBinaryReader()
{
}

IngredientBinaryReader::~IngredientBinaryReader()
{
	clear();
}

Ingredient* IngredientBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		Ingredient* ingredient = new Ingredient();

		// Читаем Название ингредиента
		string name = readString(stream);
		ingredient->setName(name);

		// Читаем Цена за ингредиент
		int price = readInt(stream);
		ingredient->setPrice(price);

		// Читаем Кол-во
		int number = readInt(stream);
		ingredient->setNumber(number);

		int numberOfEffects = readInt(stream);

		for (int i = 0; i < numberOfEffects; ++i)
		{
			int effectId = readInt(stream);
			bool isPositive = readBool(stream);

			ingredient->addEffectWithCharacteristic(effectId, isPositive);
		}

		return ingredient;
	}

	return nullptr;
}

void IngredientBinaryReader::clear()
{
}
