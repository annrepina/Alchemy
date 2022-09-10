#include "PotionTableBinaryReader.h"

PotionTableBinaryReader::PotionTableBinaryReader()
{
	this->potionBinaryReader = new PotionBinaryReader();
	this->effectsTableBinaryReader = new EffectsTableBinaryReader();
}

PotionTableBinaryReader::~PotionTableBinaryReader()
{
	clear();
}

PotionTable* PotionTableBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		PotionTable* potionTable = new PotionTable();

		// ������ Id 
		int id = readInt(stream);
		potionTable->setId(id);

		// ������ ������ �������
		int size = readInt(stream);

		// � ����� ������ ���
		for (int i = 0; i < size; ++i)
		{
			// ������ id ����� 
			int key = readInt(stream);

			// ������ �����
			Potion* potion = this->potionBinaryReader->readFromFile(path, stream);

			// ��������� � ���
			potionTable->add(potion, key);
		}

		// ������ ������� ��������
		EffectsTable* effectsTable = this->effectsTableBinaryReader->readFromFile(path, stream);
		potionTable->setEffectsTable(effectsTable);

		return potionTable;
	}

	return nullptr;
}

void PotionTableBinaryReader::clear()
{
	delete this->potionBinaryReader;
	this->potionBinaryReader = nullptr;

	delete this->effectsTableBinaryReader;
	this->effectsTableBinaryReader = nullptr;
}
