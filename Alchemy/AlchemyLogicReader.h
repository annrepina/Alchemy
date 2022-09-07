#pragma once
#include "BinaryReader.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryReader.h"

class AlchemyLogicReader : public BinaryReader< AlchemyLogic>
{
public:

	AlchemyLogicReader();

	AlchemyLogic* readFromFile(string path, ifstream& stream);

	Alchemist* returnAlchemist(string path, ifstream& stream);

private:

	AlchemistBinaryReader* alchemistBinaryReader;
};

