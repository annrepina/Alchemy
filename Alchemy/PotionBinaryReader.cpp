#include "PotionBinaryReader.h"

PotionBinaryReader::PotionBinaryReader()
{
}

PotionBinaryReader::~PotionBinaryReader()
{
	clear();
}

Potion* PotionBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		Potion* potion = new Potion();

		// читаем id эффекта
		int effectId = readInt(stream);
		potion->setEffectId(effectId);

		// читаем Цена
		int price = readInt(stream);
		potion->setPrice(price);

		// читаем Кол-во
		int number = readInt(stream);
		potion->setNumber(number);

		// Читаем Мощность зелья
		int power = readInt(stream);
		potion->setPower(power);

		return potion;
	}

	return nullptr;
}

void PotionBinaryReader::clear()
{
}
