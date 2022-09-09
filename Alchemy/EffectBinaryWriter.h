#pragma once
#include "BinaryWriter.h"
#include "Effect.h"

class EffectBinaryWriter : public BinaryWriter<Effect>
{
public:

	EffectBinaryWriter();

	~EffectBinaryWriter();

	void write(ofstream& stream, string filePath, Effect* effect) const override;

private:

	void clear() override;
};

