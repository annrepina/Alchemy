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
		
		// ������ ���-�� ��������� ���������
		int numberOfAvailableElements = readInt(stream);

		for (int i = 0; i < numberOfAvailableElements; ++i)
		{
			// ������ � ��������� id 
			int id = readInt(stream);
			ingredientsTable->addAvailableElement(id);
		}

		// ������ Id �����������
		int id = readInt(stream);
		ingredientsTable->setId(id);

		// � ������ ������ ���
		for (int i = 0; i < id; ++i)
		{
			int key = readInt(stream);

			Ingredient* ingredient = ingredientBinaryReader->readFromFile(path, stream);

			ingredientsTable->add(ingredient, key);
		}

		// ������ ������� ��������
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
