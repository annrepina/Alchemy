#pragma once
#include "BinaryReader.h"
#include "IngredientsTable.h"
#include "IngredientBinaryReader.h"
#include "EffectsTableBinaryReader.h"

class IngredientsTableBinaryReader : public BinaryReader<IngredientsTable>
{
public:

	IngredientsTableBinaryReader();

	~IngredientsTableBinaryReader();

	IngredientsTable* readFromFile(string path, ifstream& stream) override;

protected:

	void clear() override;

	IngredientBinaryReader* ingredientBinaryReader;

	EffectsTableBinaryReader* effectsTableBinaryReader;
};

