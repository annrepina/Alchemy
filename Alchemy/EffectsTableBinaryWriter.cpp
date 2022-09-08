#include "EffectsTableBinaryWriter.h"

EffectsTableBinaryWriter::EffectsTableBinaryWriter(EffectsTable* effectsTable, string filePath) : BinaryWriter(effectsTable, filePath)
{
	//this->effectBinaryWriter = nullptr;
}

EffectsTableBinaryWriter::~EffectsTableBinaryWriter()
{
	clear();
}

void EffectsTableBinaryWriter::write(ofstream& stream) const
{
	BinaryWriter::write(stream);

	// Получаем id
	int id = object->getId();
	// Пишем id 
	writeInt(stream, id);

	// Получаем размер таблицы
	int size = object->getSize();
	// Пишем размер таблицы
	writeInt(stream, size);

	// Пишем мэп с эффектами effectsWithId
	// узнаем итераторы
	auto beginIter = object->getStartIterator();
	auto endIter = object->getEndIterator();

	// Создаем эффект
	Effect* effect = new Effect();

	// создаем райтер для эффектов
	EffectBinaryWriter* effectBinaryWriter = new EffectBinaryWriter(effect, this->filePath);

	delete effect;

	effect = nullptr;

	// в цикле пишем ключ и эффект
	for (auto i = beginIter; i != endIter; ++i)
	{
		// Получаем ключ
		int key = i->first;
		// пишем ключ
		writeInt(stream, key);

		// узнаем эффект
		effect = i->second;

		// инициализируем райтер
		effectBinaryWriter->setObject(effect);

		// пишем эффект
		effectBinaryWriter->write(stream);
	}
}

void EffectsTableBinaryWriter::clear()
{
}
