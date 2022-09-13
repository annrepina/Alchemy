#pragma once
#include "BinaryWriter.h"
#include "Ingredient.h"

// Класс,который пишет класс Ingredient в файл в бинарном виде
class IngredientBinaryWriter : public BinaryWriter<Ingredient>
{
public:

	// Конструктор по умолчанию
	IngredientBinaryWriter();

	// Деструктор
	~IngredientBinaryWriter();

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string filePath, Ingredient* ingredient) const override;

private:

	// Чистит память
	void clear() override;
};