#pragma once
#include "BinaryWriter.h"
#include "Alchemist.h"
#include <fstream>

class AlchemistBinaryWriter : public BinaryWriter<Alchemist>
{
public:

	AlchemistBinaryWriter(Alchemist* alchemist, string filePath);

	~AlchemistBinaryWriter();

	void write(ofstream& stream) const override;

private:

	void clear() override;

};
