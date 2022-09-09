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

	// �������� id
	int id = effectsTable->getId();
	// ����� id 
	writeInt(stream, id);

	// �������� ������ �������
	int size = effectsTable->getSize();
	// ����� ������ �������
	writeInt(stream, size);

	// ����� ��� � ��������� effectsWithId
	// ������ ���������
	auto beginIter = effectsTable->getStartIterator();
	auto endIter = effectsTable->getEndIterator();

	// ������� ������ ��� ��������
	EffectBinaryWriter* effectBinaryWriter = new EffectBinaryWriter();

	// � ����� ����� ���� � ������
	for (auto i = beginIter; i != endIter; ++i)
	{
		// �������� ����
		int key = i->first;
		// ����� ����
		writeInt(stream, key);

		// ������ ������
		Effect* effect = i->second;

		// ����� ������
		effectBinaryWriter->write(stream, filePath, effect);
	}
}

void EffectsTableBinaryWriter::clear()
{
}
