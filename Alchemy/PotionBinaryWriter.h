#pragma once
#include "BinaryWriter.h"
#include "Potion.h"

class PotionBinaryWriter : public BinaryWriter<Potion>
{
public:

	PotionBinaryWriter();

	~PotionBinaryWriter();

	void write(ofstream& stream, string path, Potion* potion) const override;

private:

	void clear() override;

};

