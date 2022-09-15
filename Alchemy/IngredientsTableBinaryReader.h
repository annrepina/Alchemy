#pragma once
#include "BinaryReader.h"
#include "IngredientsTable.h"
#include "IngredientBinaryReader.h"
#include "EffectsTableBinaryReader.h"

// Класс, который читает класс IngredientsTable из бинарного файла
class IngredientsTableBinaryReader : public BinaryReader<IngredientsTable>
{
public:

	// Конструктор по умолчанию
	IngredientsTableBinaryReader();

	// Деструктор
	~IngredientsTableBinaryReader() override;

	// Читать из бинарного файла
	IngredientsTable* readFromFile(string path, ifstream& stream) override;

protected:

	// Очистить память
	void clear() override;

	// Класс, который читает класс Ingredient из бинарного файла
	IngredientBinaryReader* ingredientBinaryReader;

	// Класс, который читает класс EffectsTable из бинарного файла
	EffectsTableBinaryReader* effectsTableBinaryReader;
};

