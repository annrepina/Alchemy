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

		// ������ �������� �����������
		string name = readString(stream);
		ingredient->setName(name);

		// ������ ���� �� ����������
		int price = readInt(stream);
		ingredient->setPrice(price);

		// ������ ���-��
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
