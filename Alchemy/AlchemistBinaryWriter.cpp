#include "AlchemistBinaryWriter.h"

AlchemistBinaryWriter::AlchemistBinaryWriter(Alchemist& alchemist, string filePath) : BinaryWriter(alchemist, filePath)
{
}

void AlchemistBinaryWriter::write(ofstream& stream) const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	// ���� ����� �� ������, ��������� ��� ��������
	if(!stream.is_open())
		stream.open(filePath, ios::app | ios::binary | ios::trunc);

	// ������ �����
	auto nameSize = object.getName().size();

	// ����� ������ �����
	stream.write((char*)(&nameSize), sizeof(nameSize));

	// ����� ���� ���
	stream << object.getName();

	// ����� ������� ��������
	// �������� ������� ��������
	auto alchemistLevel = object.getAlchemistLevel();

	// �����
	stream.write((char*)(&alchemistLevel), sizeof(alchemistLevel));

	// ����� ������� ����������
	// �������� ������� ����������
	auto salesmanLevel = object.getSalesmanLevel();

	stream.write((char*)(&salesmanLevel), sizeof(salesmanLevel));

	// ����� �������
	// �������� �������
	auto capital = object.getCapital();

	// �����
	stream.write((char*)(&capital), sizeof(capital));

	stream.close();
}
