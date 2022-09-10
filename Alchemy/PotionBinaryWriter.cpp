#include "PotionBinaryWriter.h"

PotionBinaryWriter::PotionBinaryWriter()
{
}

PotionBinaryWriter::~PotionBinaryWriter()
{
	clear();
}

void PotionBinaryWriter::write(ofstream& stream, string path, Potion* potion) const
{
	BinaryWriter::write(stream, path, potion);

	// Получаем и пишем id эффекта
	int effectId = potion->getEffectId();
	writeInt(stream, effectId);

	// получаем и пишем Цена
	int price = potion->getPrice();
	writeInt(stream, price);

	// Получаем и пишем Кол-во
	int number = potion->getNumber();
	writeInt(stream, number);

	// Получаем и пишем Мощность зелья
	int power = potion->getPower();
	writeInt(stream, power);
}

void PotionBinaryWriter::clear()
{
}
