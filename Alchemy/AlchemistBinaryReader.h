#pragma once
#include "Alchemist.h"
#include "BinaryReader.h"
#include <fstream>

// �����, ������� ������ ����� Alchemist �� ��������� �����
class AlchemistBinaryReader : public BinaryReader<Alchemist>
{
public: 

	// �����������
	AlchemistBinaryReader();

	// ����������
	~AlchemistBinaryReader() override;

	// ������ �� ��������� �����
	Alchemist* readFromFile(string path, ifstream& stream) override;

private:

	// �������� ������
	void clear() override;
};

