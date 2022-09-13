#include "IngredientsTableBinaryReader.h"

IngredientsTableBinaryReader::IngredientsTableBinaryReader()
{
	this->ingredientBinaryReader = new IngredientBinaryReader();
	this->effectsTableBinaryReader = new EffectsTableBinaryReader();
}

IngredientsTableBinaryReader::~IngredientsTableBinaryReader()
{
	clear();
}

IngredientsTable* IngredientsTableBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		IngredientsTable* ingredientsTable = new IngredientsTable();
		
		// читаем кол-во доступных элементов
		int numberOfAvailableElements = readInt(stream);

		for (int i = 0; i < numberOfAvailableElements; ++i)
		{
			// Читаем и добавляем id 
			int id = readInt(stream);
			ingredientsTable->addAvailableElement(id);
		}

		// Читаем Id ингредиента
		int id = readInt(stream);
		ingredientsTable->setId(id);

		// В циекле читаем мэп
		for (int i = 0; i < id; ++i)
		{
			int key = readInt(stream);

			Ingredient* ingredient = ingredientBinaryReader->readFromFile(path, stream);

			ingredientsTable->add(ingredient, key);
		}

		// Читаем Таблица эффектов
		EffectsTable* effectsTable = effectsTableBinaryReader->readFromFile(path, stream);
		ingredientsTable->setEffectsTable(effectsTable);

		return ingredientsTable;
	}

	return nullptr;
}

void IngredientsTableBinaryReader::clear()
{
	delete this->ingredientBinaryReader;
	this->ingredientBinaryReader = nullptr;

	delete this->effectsTableBinaryReader;
	this->effectsTableBinaryReader = nullptr;
}
