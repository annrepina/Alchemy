#pragma once
#include "BinaryWriter.h"
#include "Effect.h"

class EffectBinaryWriter : public BinaryWriter<Effect>
{
public:

	EffectBinaryWriter(Effect* effect, string filePath);

	~EffectBinaryWriter();

	void write(ofstream& stream) const override;

private:

	void clear() override;
};

