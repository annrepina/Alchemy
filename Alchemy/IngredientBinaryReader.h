#pragma once
#include "BinaryReader.h"
#include "Ingredient.h"

// Класс, который читает класс Ingredient из бинарного файла
class IngredientBinaryReader : public BinaryReader<Ingredient>
{
public:

	// Конструктор по умолчанию
	IngredientBinaryReader();

	// Деструктор
	~IngredientBinaryReader() override;

	// Читать из бинарного файла
	Ingredient* readFromFile(string path, ifstream& stream) override;

protected: 

	// Очистить из памяти
	void clear() override;
};

