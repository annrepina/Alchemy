#pragma once
#include "BinaryReader.h"
#include "Potion.h"

class PotionBinaryReader : public BinaryReader<Potion>
{
public:

	PotionBinaryReader();

	~PotionBinaryReader();

	Potion* readFromFile(string path, ifstream& stream) override;

private:

	void clear() override;
};

