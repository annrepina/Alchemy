#pragma once
#include "BinaryWriter.h"
#include "Alchemist.h"
#include <fstream>

class AlchemistBinaryWriter : public BinaryWriter<Alchemist>
{
public:

	AlchemistBinaryWriter(/*Alchemist* alchemist, string filePath*/);

	~AlchemistBinaryWriter();

	void write(ofstream& stream, string filePath, Alchemist* alchemist) const override;

private:

	void clear() override;

};
