#pragma once

#include "Ingredient.h"

class IngredientBuilder
{
public:

	// ����������� �� ���������
	IngredientBuilder();

	// ����������
	~IngredientBuilder();

	// ������ ���
	void setName(string name);

	// ������ ����
	void setPrice(float price);

	// �������� ������
	void addEffect(int effectId);

	// �������� ���������
	Ingredient* getResult();

private:

	// ��������� �����������
	Ingredient* ingredient;

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();

	// ������ ���� ������������
	static string listOfIngredientsNames[100];

	// ������ ���� ��������
	static string listOfEffectsNames[55];
};

