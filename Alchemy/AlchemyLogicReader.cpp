#include "AlchemyLogicReader.h"

AlchemyLogicReader::AlchemyLogicReader()
{
	this->alchemistBinaryReader = new AlchemistBinaryReader();
	this->effectsTableBinaryReader = new EffectsTableBinaryReader();
	this->ingredientsTableBinaryReader = new IngredientsTableBinaryReader();
	this->potionTableBinaryReader = new PotionTableBinaryReader();
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

	// ������ ������� ������������
	IngredientsTable* ingredientsTable = ingredientsTableBinaryReader->readFromFile(path, stream);
	alchemyLogic->setIngredientsTable(ingredientsTable);

	// ������ ������� �����
	PotionTable* potionTable = potionTableBinaryReader->readFromFile(path, stream);
	alchemyLogic->setPotionTable(potionTable);

	stream.close();

	return alchemyLogic;
}

void AlchemyLogicReader::clear()
{
	if (nullptr != this->alchemistBinaryReader)
	{
		delete this->alchemistBinaryReader;
		this->alchemistBinaryReader = nullptr;
	}

	if (nullptr != this->effectsTableBinaryReader)
	{
		delete this->effectsTableBinaryReader;
		this->effectsTableBinaryReader = nullptr;
	}

	if (nullptr != this->ingredientsTableBinaryReader)
	{
		delete this->ingredientsTableBinaryReader;
		this->ingredientsTableBinaryReader = nullptr;
	}

	if (nullptr != this->potionTableBinaryReader)
	{
		delete this->potionTableBinaryReader;
		this->potionTableBinaryReader = nullptr;
	}
}