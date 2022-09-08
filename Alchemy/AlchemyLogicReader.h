#pragma once
#include "BinaryReader.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryReader.h"
#include "EffectsTableBinaryReader.h"

class AlchemyLogicReader : public BinaryReader< AlchemyLogic>
{
public:

	AlchemyLogicReader();

	~AlchemyLogicReader();

	AlchemyLogic* readFromFile(string path, ifstream& stream);

	Alchemist* returnAlchemist(string path, ifstream& stream);

private:

	AlchemistBinaryReader* alchemistBinaryReader;

	EffectsTableBinaryReader* effectsTableBinaryReader;



	void clear() override;
};

