#include "IngredientsTableBinaryWriter.h"

IngredientsTableBinaryWriter::IngredientsTableBinaryWriter()
{
	ingredientBinaryWriter = new IngredientBinaryWriter();
	effectsTableBinaryWriter = new EffectsTableBinaryWriter();
}

IngredientsTableBinaryWriter::~IngredientsTableBinaryWriter()
{
	clear();
}

void IngredientsTableBinaryWriter::write(ofstream& stream, string filePath, IngredientsTable* ingredientsTable) const
{
	BinaryWriter::write(stream, filePath, ingredientsTable);

	// получаем и пишем кол-во доступных элементов 
	int numberOfAvailableElements = ingredientsTable->getNumberOfAvailableElements();
	writeInt(stream, numberOfAvailableElements);

	// узнаем итераторы на вектор с id доступных элементов
	auto beginIter = ingredientsTable->getBeginIteratorOfAvailableElements();
	auto endIter = ingredientsTable->getEndIteratorOfAvailableElements();

	// в цикле пишем значения
	for (auto i = beginIter; i != endIter; ++i)
	{
		// получаем значение и пишем
		int value = *i;
		writeInt(stream, value);
	}

	// Получаем и пишем Id ингредиента
	int id = ingredientsTable->getId();
	writeInt(stream, id);

	// узнаем итераторы на мэп
	auto beginIterOfMap = ingredientsTable->getStartIterator();
	auto endIterOfMap = ingredientsTable->getEndIterator();

	// в цикле пишем значения
	for (auto i = beginIterOfMap; i != endIterOfMap; ++i)
	{
		// Получаем и пишем id
		int key = i->first;
		writeInt(stream, key);

		// Получаем и пишем ингредиент
		Ingredient* ingredient = i->second;
		ingredientBinaryWriter->write(stream, filePath, ingredient);
	}

	// Получаем и пишем Таблица эффектов
	EffectsTable* effectsTable = ingredientsTable->getEffectsTable();
	effectsTableBinaryWriter->write(stream, filePath, effectsTable);
}

void IngredientsTableBinaryWriter::clear()
{
	delete this->ingredientBinaryWriter;
	this->ingredientBinaryWriter = nullptr;

	delete this->effectsTableBinaryWriter;
	this->effectsTableBinaryWriter = nullptr;
}
