#pragma once
#include "BinaryReader.h"
#include "EffectsTable.h"
#include "EffectBinaryReader.h"

class EffectsTableBinaryReader : public BinaryReader<EffectsTable>
{
public:

	EffectsTableBinaryReader();

	~EffectsTableBinaryReader();

	EffectsTable* readFromFile(string path, ifstream& stream) override;

private:

	void clear() override;
};

