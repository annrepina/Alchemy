#pragma once
#include "BinaryWriter.h"
#include "IngredientsTable.h"
#include "IngredientBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

// Класс,который пишет класс IngredientsTable в файл в бинарном виде
class IngredientsTableBinaryWriter : BinaryWriter<IngredientsTable>
{
public:

	// Конструктор по умолчанию
	IngredientsTableBinaryWriter();

	// Деструктор
	~IngredientsTableBinaryWriter();

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string filePath, IngredientsTable* ingredientsTable) const override;

private:

	// Чистит память
	void clear() override;

	// Класс,который пишет класс Ingredient в файл в бинарном виде
	IngredientBinaryWriter* ingredientBinaryWriter;

	// Класс,который пишет класс EffectsTable в файл в бинарном виде
	EffectsTableBinaryWriter* effectsTableBinaryWriter;
};

