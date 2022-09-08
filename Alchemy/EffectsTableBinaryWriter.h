#pragma once
#include "BinaryWriter.h"
#include "EffectsTable.h"
#include "EffectBinaryWriter.h"

class EffectsTableBinaryWriter : public BinaryWriter<EffectsTable>
{
public:

	EffectsTableBinaryWriter(EffectsTable* effectsTable, string filePath);

	~EffectsTableBinaryWriter();

	void write(ofstream& stream) const override;

protected:

	void clear() override;

	//EffectBinaryWriter* effectBinaryWriter;
};

