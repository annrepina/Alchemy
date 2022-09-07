#pragma once
#include "Alchemist.h"
#include "BinaryReader.h"
#include <fstream>

class AlchemistBinaryReader : public BinaryReader<Alchemist>
{
public: 

	// �����������
	AlchemistBinaryReader();

	Alchemist* readFromFile(string path, ifstream& stream) override;

private:

	//string path;
};

