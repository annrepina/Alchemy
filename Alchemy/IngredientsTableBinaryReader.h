#pragma once
#include "BinaryReader.h"
#include "IngredientsTable.h"
#include "IngredientBinaryReader.h"
#include "EffectsTableBinaryReader.h"

// �����, ������� ������ ����� IngredientsTable �� ��������� �����
class IngredientsTableBinaryReader : public BinaryReader<IngredientsTable>
{
public:

	// ����������� �� ���������
	IngredientsTableBinaryReader();

	// ����������
	~IngredientsTableBinaryReader() override;

	// ������ �� ��������� �����
	IngredientsTable* readFromFile(string path, ifstream& stream) override;

protected:

	// �������� ������
	void clear() override;

	// �����, ������� ������ ����� Ingredient �� ��������� �����
	IngredientBinaryReader* ingredientBinaryReader;

	// �����, ������� ������ ����� EffectsTable �� ��������� �����
	EffectsTableBinaryReader* effectsTableBinaryReader;
};

