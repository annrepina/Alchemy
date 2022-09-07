#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist& alchemist, string filePath) : BinaryWriter(alchemist, filePath)
{
}

void AlchemistBinaryWriter::write(ofstream& stream) const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	// ЕСЛИ СТРИМ НЕ ОТКРЫТ, открываем для дозаписи
	if(!stream.is_open())
		stream.open(filePath, ios::app | ios::binary | ios::trunc);

	// размер имени
	auto nameSize = object.getName().size();

	// пишем размер имени
	stream.write((char*)(&nameSize), sizeof(nameSize));

	// пишем само имя
	stream << object.getName();

	// пишем уровень алхимика
	// получаем уровень алхимика
	auto alchemistLevel = object.getAlchemistLevel();

	// пишем
	stream.write((char*)(&alchemistLevel), sizeof(alchemistLevel));

	// пишем уровень продажника
	// получаем уровень продажника
	auto salesmanLevel = object.getSalesmanLevel();

	stream.write((char*)(&salesmanLevel), sizeof(salesmanLevel));

	// пишем капитал
	// получаем капитал
	auto capital = object.getCapital();

	// пишем
	stream.write((char*)(&capital), sizeof(capital));

	stream.close();
}
