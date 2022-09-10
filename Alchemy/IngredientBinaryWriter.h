#pragma once
#include "BinaryWriter.h"
#include "Ingredient.h"

class IngredientBinaryWriter : public BinaryWriter<Ingredient>
{
public:

	IngredientBinaryWriter();

	~IngredientBinaryWriter();

	void write(ofstream& stream, string filePath, Ingredient* ingredient) const override;

private:

	void clear() override;
};

