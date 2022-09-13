#pragma once
#include "BinaryWriter.h"
#include "Alchemist.h"
#include <fstream>

// �����,������� ����� ����� AlchemistBinary � ���� � �������� ����
class AlchemistBinaryWriter : public BinaryWriter<Alchemist>
{
public:

	// ����������� �� ���������
	AlchemistBinaryWriter();

	// ����������
	~AlchemistBinaryWriter();

	// ������ � ���� � �������� ����
	void write(ofstream& stream, string filePath, Alchemist* alchemist) const override;

private:

	// �������� ������
	void clear() override;

};