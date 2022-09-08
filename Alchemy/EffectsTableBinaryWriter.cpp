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

	// �������� id
	int id = object->getId();
	// ����� id 
	writeInt(stream, id);

	// �������� ������ �������
	int size = object->getSize();
	// ����� ������ �������
	writeInt(stream, size);

	// ����� ��� � ��������� effectsWithId
	// ������ ���������
	auto beginIter = object->getStartIterator();
	auto endIter = object->getEndIterator();

	// ������� ������
	Effect* effect = new Effect();

	// ������� ������ ��� ��������
	EffectBinaryWriter* effectBinaryWriter = new EffectBinaryWriter(effect, this->filePath);

	delete effect;

	effect = nullptr;

	// � ����� ����� ���� � ������
	for (auto i = beginIter; i != endIter; ++i)
	{
		// �������� ����
		int key = i->first;
		// ����� ����
		writeInt(stream, key);

		// ������ ������
		effect = i->second;

		// �������������� ������
		effectBinaryWriter->setObject(effect);

		// ����� ������
		effectBinaryWriter->write(stream);
	}
}

void EffectsTableBinaryWriter::clear()
{
}
