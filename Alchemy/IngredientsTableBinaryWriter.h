#pragma once
#include "BinaryWriter.h"
#include "IngredientsTable.h"
#include "IngredientBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

// �����,������� ����� ����� IngredientsTable � ���� � �������� ����
class IngredientsTableBinaryWriter : BinaryWriter<IngredientsTable>
{
public:

	// ����������� �� ���������
	IngredientsTableBinaryWriter();

	// ����������
	~IngredientsTableBinaryWriter();

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string filePath, IngredientsTable* ingredientsTable) const override;

private:

	// ������ ������
	void clear() override;

	// �����,������� ����� ����� Ingredient � ���� � �������� ����
	IngredientBinaryWriter* ingredientBinaryWriter;

	// �����,������� ����� ����� EffectsTable � ���� � �������� ����
	EffectsTableBinaryWriter* effectsTableBinaryWriter;
};

