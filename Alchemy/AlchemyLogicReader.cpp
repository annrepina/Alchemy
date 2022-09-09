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

	// ��������� ����
	stream.open(path, std::ios::binary);

	// ������ ��������
	Alchemist* alchemist = alchemistBinaryReader->readFromFile(path, stream);
	alchemyLogic->setAlchemist(alchemist);

	// ������ ������� ��������
	EffectsTable* effectsTable = effectsTableBinaryReader->readFromFile(path, stream);
	alchemyLogic->setEffectsTable(effectsTable);




	stream.close();

	return alchemyLogic;
}

void AlchemyLogicReader::clear()
{
	delete this->alchemistBinaryReader;
}
