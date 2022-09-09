#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter()
{
}

AlchemistBinaryWriter::~AlchemistBinaryWriter()
{
	clear();
}

void AlchemistBinaryWriter::write(ofstream& stream, string filePath, Alchemist* alchemist) const
{
	BinaryWriter::write(stream, filePath, alchemist);

	// Получаем имя
	string name = alchemist->getName();
	// пишем имя
	writeString(stream, name);

	// получаем уровень алхимика
	int alchemistLevel = alchemist->getAlchemistLevel();
	// пишем уровень алхимика
	writeInt(stream, alchemistLevel);

	// получаем уровень продажника
	int salesmanLevel = alchemist->getSalesmanLevel();
	// пишем уровень продажника
	writeInt(stream, salesmanLevel);

	// получаем капитал
	auto capital = alchemist->getCapital();
	// пишем капитал
	writeInt(stream, capital);
}

void AlchemistBinaryWriter::clear()
{
}
