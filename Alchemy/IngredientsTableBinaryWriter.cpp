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

	// �������� � ����� ���-�� ��������� ��������� 
	int numberOfAvailableElements = ingredientsTable->getNumberOfAvailableElements();
	writeInt(stream, numberOfAvailableElements);

	// ������ ��������� �� ������ � id ��������� ���������
	auto beginIter = ingredientsTable->getBeginIteratorOfAvailableElements();
	auto endIter = ingredientsTable->getEndIteratorOfAvailableElements();

	// � ����� ����� ��������
	for (auto i = beginIter; i != endIter; ++i)
	{
		// �������� �������� � �����
		int value = *i;
		writeInt(stream, value);
	}

	// �������� � ����� Id �����������
	int id = ingredientsTable->getId();
	writeInt(stream, id);

	// ������ ��������� �� ���
	auto beginIterOfMap = ingredientsTable->getStartIterator();
	auto endIterOfMap = ingredientsTable->getEndIterator();

	// � ����� ����� ��������
	for (auto i = beginIterOfMap; i != endIterOfMap; ++i)
	{
		// �������� � ����� id
		int key = i->first;
		writeInt(stream, key);

		// �������� � ����� ����������
		Ingredient* ingredient = i->second;
		ingredientBinaryWriter->write(stream, filePath, ingredient);
	}

	// �������� � ����� ������� ��������
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
