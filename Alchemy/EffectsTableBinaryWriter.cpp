#include "EffectsTableBinaryWriter.h"

EffectsTableBinaryWriter::EffectsTableBinaryWriter()
{
	// ������� ������ ��� ��������
	this->effectBinaryWriter = new EffectBinaryWriter();
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
		this->effectBinaryWriter->write(stream, filePath, effect);
	}
}

void EffectsTableBinaryWriter::clear()
{
	delete this->effectBinaryWriter;
	this->effectBinaryWriter = nullptr;
}
