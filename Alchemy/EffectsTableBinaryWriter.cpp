#include "EffectsTableBinaryWriter.h"

EffectsTableBinaryWriter::EffectsTableBinaryWriter()
{
}

EffectsTableBinaryWriter::~EffectsTableBinaryWriter()
{
	clear();
}

void EffectsTableBinaryWriter::write(ofstream& stream, string filePath, EffectsTable* effectsTable) const
{
	BinaryWriter::write(stream, filePath, effectsTable);

	// Получаем id
	int id = effectsTable->getId();
	// Пишем id 
	writeInt(stream, id);

	// Получаем размер таблицы
	int size = effectsTable->getSize();
	// Пишем размер таблицы
	writeInt(stream, size);

	// Пишем мэп с эффектами effectsWithId
	// узнаем итераторы
	auto beginIter = effectsTable->getStartIterator();
	auto endIter = effectsTable->getEndIterator();

	// создаем райтер для эффектов
	EffectBinaryWriter* effectBinaryWriter = new EffectBinaryWriter();

	// в цикле пишем ключ и эффект
	for (auto i = beginIter; i != endIter; ++i)
	{
		// Получаем ключ
		int key = i->first;
		// пишем ключ
		writeInt(stream, key);

		// узнаем эффект
		Effect* effect = i->second;

		// пишем эффект
		effectBinaryWriter->write(stream, filePath, effect);
	}
}

void EffectsTableBinaryWriter::clear()
{
}
