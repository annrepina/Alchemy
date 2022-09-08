#pragma once
#include "BinaryReader.h"
#include "Effect.h"

class EffectBinaryReader : public BinaryReader<Effect>
{
public:

	EffectBinaryReader();

	~EffectBinaryReader();

	Effect* readFromFile(string path, ifstream& stream) override;

private:

	void clear() override;
};

