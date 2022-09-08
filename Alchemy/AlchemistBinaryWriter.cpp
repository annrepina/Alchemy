#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist* alchemist, string filePath) : BinaryWriter(alchemist, filePath)
{
}

AlchemistBinaryWriter::~AlchemistBinaryWriter()
{
	clear();
}

void AlchemistBinaryWriter::write(ofstream& stream) const
{
	BinaryWriter::write(stream);

	// Получаем имя
	string name = object->getName();
	// пишем имя
	writeString(stream, name);

	// получаем уровень алхимика
	int alchemistLevel = object->getAlchemistLevel();
	// пишем уровень алхимика
	writeInt(stream, alchemistLevel);

	// получаем уровень продажника
	int salesmanLevel = object->getSalesmanLevel();
	// пишем уровень продажника
	writeInt(stream, salesmanLevel);

	// получаем капитал
	auto capital = object->getCapital();
	// пишем капитал
	writeInt(stream, capital);
}

void AlchemistBinaryWriter::clear()
{
}
