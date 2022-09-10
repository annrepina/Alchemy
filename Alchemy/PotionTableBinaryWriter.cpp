#include "PotionTableBinaryWriter.h"

PotionTableBinaryWriter::PotionTableBinaryWriter()
{
	this->potionBinaryWriter = new PotionBinaryWriter();
	this->effectsTableBinaryWriter = new EffectsTableBinaryWriter();
}

PotionTableBinaryWriter::~PotionTableBinaryWriter()
{
	clear();
}

void PotionTableBinaryWriter::write(ofstream& stream, string path, PotionTable* potionTable) const
{
	BinaryWriter::write(stream, path, potionTable);

	// Получаем и пишем Id 
	int id = potionTable->getId();
	writeInt(stream, id);

	// Получаем и пишем размер таблицы
	int size = potionTable->getSize();
	writeInt(stream, size);

	// Получаем итераторы мэп
	auto beginIter = potionTable->getStartIterator();
	auto endIter = potionTable->getEndIterator();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// Получаем и пишем id зелья 
		int key = i->first;
		writeInt(stream, key);

		// Получаем и пишем зелье
		Potion* potion = i->second;
		this->potionBinaryWriter->write(stream, path, potion);
	}

	// Получаем и пишем Таблица эффектов
	EffectsTable* effectsTable = potionTable->getEffectsTable();
	this->effectsTableBinaryWriter->write(stream, path, effectsTable);
}

void PotionTableBinaryWriter::clear()
{
	delete this->potionBinaryWriter;
	this->potionBinaryWriter = nullptr;

	delete this->effectsTableBinaryWriter;
	this->effectsTableBinaryWriter = nullptr;
}
