#include "AlchemyLogicReader.h"

AlchemyLogicReader::AlchemyLogicReader()
{
	this->alchemistBinaryReader = new AlchemistBinaryReader();
	this->effectsTableBinaryReader = new EffectsTableBinaryReader();
	this->effectBinaryReader = new EffectBinaryReader();
}

AlchemyLogicReader::~AlchemyLogicReader()
{
	clear();
}

AlchemyLogic* AlchemyLogicReader::readFromFile(string path, ifstream& stream)
{
	//stream.open(stream, ios::in);

	AlchemyLogic* alchemyLogic = new AlchemyLogic();

	// ��������� ����
	stream.open(path, std::ios::binary);

	// ������ ��������
	Alchemist* alchemist = alchemistBinaryReader->readFromFile(path, stream);
	alchemyLogic->setAlchemist(alchemist);

	//Effect* effect = effectBinaryReader->readFromFile(path, stream);

	// ������ ������� ��������
	EffectsTable* effectsTable = effectsTableBinaryReader->readFromFile(path, stream);
	alchemyLogic->setEffectsTable(effectsTable);




	stream.close();

	return alchemyLogic;
}

Alchemist* AlchemyLogicReader::returnAlchemist(string path, ifstream& stream)
{
	// ��������� ����
	stream.open(path);

	return alchemistBinaryReader->readFromFile(path, stream);

	stream.close();
}

void AlchemyLogicReader::clear()
{
	delete this->alchemistBinaryReader;
}
