#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>

#define NUMBER_OF_COLUMNS		6		// ���-�� �������

// ������� ������������
class IngredientsTable : public Table
{
public:

	// ����������� �� ���������
	IngredientsTable();

	~IngredientsTable();

	// �������� ���������� � �������
	void addIngredient(Ingredient* ingredient);

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ������ �������
	void print() const override;

private:

	// Id �����������
	static int id;

	// �����������
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	void clear();

	void calculateLength() override;

	// ������� ���������� id
	int calculateMaxStrIdSize();

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize();

	// ������� ���������� ���-�� ������������
	int calculateMaxNumber();

};

