#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist& alchemist, string filePath)
		: alchemist(alchemist), filePath(filePath)
{
}

void AlchemistBinaryWriter::write() const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	ofstream stream(filePath, ios::out | ios::binary | ios::trunc);

	// ������ �����
	auto nameSize = alchemist.getName().size();

	// ����� ������ �����
	stream.write((char*)(&nameSize), sizeof(nameSize));

	// ����� ���� ���
	stream << alchemist.getName();

	// ����� ������� ��������
	stream.write((char*)(alchemist.getAlchemistLevel()), sizeof(alchemist.getAlchemistLevel()));

	// ����� ������� ����������
	stream.write((char*)(alchemist.getSalesmanLevel()), sizeof(alchemist.getSalesmanLevel()));

	// ����� �������
	stream.write((char*)(alchemist.getCapital()), sizeof(alchemist.getCapital()));

	stream.close();
}
