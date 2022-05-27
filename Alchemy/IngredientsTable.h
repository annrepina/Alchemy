#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include <map>

// ������� ������������
class IngredientsTable
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
	void print();

private:

	// Id �����������
	static int id;

	// �����������
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	void clear();

};

