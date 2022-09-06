#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist& alchemist, string filePath)
		: alchemist(alchemist), filePath(filePath)
{
}

void AlchemistBinaryWriter::write() const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	ofstream stream(filePath, ios::out | ios::binary | ios::trunc);

	// размер имени
	auto nameSize = alchemist.getName().size();

	// пишем размер имени
	stream.write((char*)(&nameSize), sizeof(nameSize));

	// пишем само имя
	stream << alchemist.getName();

	// пишем уровень алхимика
	stream.write((char*)(alchemist.getAlchemistLevel()), sizeof(alchemist.getAlchemistLevel()));

	// пишем уровень продажника
	stream.write((char*)(alchemist.getSalesmanLevel()), sizeof(alchemist.getSalesmanLevel()));

	// пишем капитал
	stream.write((char*)(alchemist.getCapital()), sizeof(alchemist.getCapital()));

	stream.close();
}
