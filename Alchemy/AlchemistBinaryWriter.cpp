#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist* alchemist, string filePath) : BinaryWriter(alchemist, filePath)
{
}

AlchemistBinaryWriter::~AlchemistBinaryWriter()
{
	clear();
}

void AlchemistBinaryWriter::write(ofstream& stream) const
{
	BinaryWriter::write(stream);

	// �������� ���
	string name = object->getName();
	// ����� ���
	writeString(stream, name);

	// �������� ������� ��������
	int alchemistLevel = object->getAlchemistLevel();
	// ����� ������� ��������
	writeInt(stream, alchemistLevel);

	// �������� ������� ����������
	int salesmanLevel = object->getSalesmanLevel();
	// ����� ������� ����������
	writeInt(stream, salesmanLevel);

	// �������� �������
	auto capital = object->getCapital();
	// ����� �������
	writeInt(stream, capital);
}

void AlchemistBinaryWriter::clear()
{
}
