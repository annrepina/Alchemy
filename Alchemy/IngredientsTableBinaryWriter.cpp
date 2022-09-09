#include "IngredientsTableBinaryWriter.h"

IngredientsTableBinaryWriter::IngredientsTableBinaryWriter()
{
}

IngredientsTableBinaryWriter::~IngredientsTableBinaryWriter()
{
	clear();
}

void IngredientsTableBinaryWriter::write(ofstream& stream, string filePath, IngredientsTable* ingredientsTable) const
{
	BinaryWriter::write(stream, filePath, ingredientsTable);


	// Доступные пользователю элементы, те, у которых кол-во больше нуля
	vector<int> availableElements;

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();
}

void IngredientsTableBinaryWriter::clear()
{
}
