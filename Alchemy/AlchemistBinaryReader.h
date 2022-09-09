#pragma once
#include "Alchemist.h"
#include "BinaryReader.h"
#include <fstream>

class AlchemistBinaryReader : public BinaryReader<Alchemist>
{
public: 

	// Конструктор
	AlchemistBinaryReader();

	~AlchemistBinaryReader();

	Alchemist* readFromFile(string path, ifstream& stream) override;

private:

	void clear() override;
};

