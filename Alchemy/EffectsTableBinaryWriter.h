#pragma once
#include "BinaryWriter.h"
#include "EffectsTable.h"
#include "EffectBinaryWriter.h"

class EffectsTableBinaryWriter : public BinaryWriter<EffectsTable>
{
public:

	EffectsTableBinaryWriter();

	~EffectsTableBinaryWriter();

	void write(ofstream& stream, string filePath, EffectsTable* effectsTable) const override;

protected:

	void clear() override;
};

