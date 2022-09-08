#include "EffectBinaryWriter.h"

EffectBinaryWriter::EffectBinaryWriter(Effect* effect, string filePath) : BinaryWriter(effect, filePath)
{

}

EffectBinaryWriter::~EffectBinaryWriter()
{
	clear();
}

void EffectBinaryWriter::write(ofstream& stream) const
{
	BinaryWriter::write(stream);

	// Получаем имя
	string name = object->getName();
	// пишем имя 
	writeString(stream, name);

	// Получаем Булева переменная, отвечающая позитивный или негативный эффект
	bool isPositive = object->getIsPositive();
	writeBool(stream, isPositive);
}

void EffectBinaryWriter::clear()
{
}
