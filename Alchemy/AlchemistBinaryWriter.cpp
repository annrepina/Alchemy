#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter()
{
}

AlchemistBinaryWriter::~AlchemistBinaryWriter()
{
	clear();
}

void AlchemistBinaryWriter::write(ofstream& stream, string filePath, Alchemist* alchemist) const
{
	BinaryWriter::write(stream, filePath, alchemist);

	// �������� ���
	string name = alchemist->getName();
	// ����� ���
	writeString(stream, name);

	// �������� ������� ��������
	int alchemistLevel = alchemist->getAlchemistLevel();
	// ����� ������� ��������
	writeInt(stream, alchemistLevel);

	// �������� ������� ����������
	int salesmanLevel = alchemist->getSalesmanLevel();
	// ����� ������� ����������
	writeInt(stream, salesmanLevel);

	// �������� �������
	auto capital = alchemist->getCapital();
	// ����� �������
	writeInt(stream, capital);
}

void AlchemistBinaryWriter::clear()
{
}
