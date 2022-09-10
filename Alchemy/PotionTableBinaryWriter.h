#pragma once
#include "BinaryWriter.h"
#include "PotionTable.h"
#include "PotionBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

class PotionTableBinaryWriter : public BinaryWriter<PotionTable>
{
public:

	PotionTableBinaryWriter();

	~PotionTableBinaryWriter();

	void write(ofstream& stream, string path, PotionTable* potionTable) const override;

private:

	void clear() override;

	PotionBinaryWriter* potionBinaryWriter;

	EffectsTableBinaryWriter* effectsTableBinaryWriter;
};

