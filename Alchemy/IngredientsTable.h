#pragma once
#include "Ingredient.h"

// ������� ������������
class IngredientsTable
{
public:

	// ����������� �� ���������
	IngredientsTable();

	~IngredientsTable();

	void addIngredient(Ingredient* ingredient);

private:

	// �����������
	vector <Ingredient*> ingredients;

	void clear();

};

