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

		// Читаем Id 
		int id = readInt(stream);
		potionTable->setId(id);

		// Читаем размер таблицы
		int size = readInt(stream);

		// В цикле читаем мэп
		for (int i = 0; i < size; ++i)
		{
			// Читаем id зелья 
			int key = readInt(stream);

			// Читаем зелье
			Potion* potion = this->potionBinaryReader->readFromFile(path, stream);

			// добавляем в мэп
			potionTable->add(potion, key);
		}

		// Читаем Таблица эффектов
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
