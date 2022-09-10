#pragma once
#include "BinaryReader.h"
#include "PotionTable.h"
#include "PotionBinaryReader.h"
#include "EffectsTableBinaryReader.h"

class PotionTableBinaryReader : public BinaryReader<PotionTable>
{
public:

	PotionTableBinaryReader();

	~PotionTableBinaryReader();

	PotionTable* readFromFile(string path, ifstream& stream) override;

private:

	void clear() override;

	PotionBinaryReader* potionBinaryReader;

	EffectsTableBinaryReader* effectsTableBinaryReader;
};

