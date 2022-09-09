#include "EffectBinaryWriter.h"

EffectBinaryWriter::EffectBinaryWriter()
{

}

EffectBinaryWriter::~EffectBinaryWriter()
{
	clear();
}

void EffectBinaryWriter::write(ofstream& stream, string filePath, Effect* effect) const
{
	BinaryWriter::write(stream, filePath, effect);

	// Получаем имя
	string name = effect->getName();
	// пишем имя 
	writeString(stream, name);

	// Получаем Булева переменная, отвечающая позитивный или негативный эффект
	bool isPositive = effect->getIsPositive();
	writeBool(stream, isPositive);
}

void EffectBinaryWriter::clear()
{
}
