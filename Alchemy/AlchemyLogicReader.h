#pragma once
#include "BinaryReader.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryReader.h"
#include "EffectsTableBinaryReader.h"
#include "IngredientsTableBinaryReader.h"
#include "PotionTableBinaryReader.h"

class AlchemyLogicReader : public BinaryReader< AlchemyLogic>
{
public:

	AlchemyLogicReader();

	~AlchemyLogicReader();

	AlchemyLogic* readFromFile(string path, ifstream& stream);

private:

	AlchemistBinaryReader* alchemistBinaryReader;

	EffectsTableBinaryReader* effectsTableBinaryReader;

	IngredientsTableBinaryReader* ingredientsTableBinaryReader;

	PotionTableBinaryReader* potionTableBinaryReader;

	void clear() override;
};

