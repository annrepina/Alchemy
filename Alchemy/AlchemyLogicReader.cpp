#include "AlchemyLogicReader.h"

AlchemyLogicReader::AlchemyLogicReader()
{
	this->alchemistBinaryReader = new AlchemistBinaryReader();
	this->effectsTableBinaryReader = new EffectsTableBinaryReader();
}

AlchemyLogicReader::~AlchemyLogicReader()
{
	clear();
}

AlchemyLogic* AlchemyLogicReader::readFromFile(string path, ifstream& stream)
{
	AlchemyLogic* alchemyLogic = new AlchemyLogic();

	// открываем файл
	stream.open(path, std::ios::binary);

	// читаем алхимика
	Alchemist* alchemist = alchemistBinaryReader->readFromFile(path, stream);
	alchemyLogic->setAlchemist(alchemist);

	// Читаем таблицу эффектов
	EffectsTable* effectsTable = effectsTableBinaryReader->readFromFile(path, stream);
	alchemyLogic->setEffectsTable(effectsTable);




	stream.close();

	return alchemyLogic;
}

void AlchemyLogicReader::clear()
{
	delete this->alchemistBinaryReader;
}
