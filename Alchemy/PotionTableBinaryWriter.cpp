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

	// �������� � ����� ���-�� ��������� ��������� 
	int numberOfAvailableElements = potionTable->getNumberOfAvailableElements();
	writeInt(stream, numberOfAvailableElements);

	// ������ ��������� �� ������ � id ��������� ���������
	auto beginAvailableIter = potionTable->getBeginIteratorOfAvailableElements();
	auto endAvailableIter = potionTable->getEndIteratorOfAvailableElements();

	// � ����� ����� ��������
	for (auto i = beginAvailableIter; i != endAvailableIter; ++i)
	{
		// �������� �������� � �����
		int value = *i;
		writeInt(stream, value);
	}

	// �������� � ����� Id 
	int id = potionTable->getId();
	writeInt(stream, id);

	// �������� � ����� ������ �������
	int size = potionTable->getSize();
	writeInt(stream, size);

	// �������� ��������� ���
	auto beginIter = potionTable->getStartIterator();
	auto endIter = potionTable->getEndIterator();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// �������� � ����� id ����� 
		int key = i->first;
		writeInt(stream, key);

		// �������� � ����� �����
		Potion* potion = i->second;
		this->potionBinaryWriter->write(stream, path, potion);
	}

	// �������� � ����� ������� ��������
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
