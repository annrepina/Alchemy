#include "EffectBinaryReader.h"
#include <iostream>

EffectBinaryReader::EffectBinaryReader()
{
}

EffectBinaryReader::~EffectBinaryReader()
{
	clear();
}

Effect* EffectBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		Effect* effect = new Effect();

		// Название эффекта
		string name = readString(stream);
		effect->setName(name);

		bool isPositive = readBool(stream);
		effect->setIsPositive(isPositive);

		return effect;
	}

	return nullptr;
}

void EffectBinaryReader::clear()
{
}
