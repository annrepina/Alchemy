#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Builder.h"

#define NUMBER_OF_INGREDIENTS		100		// ���-�� ������������

// ��������� ������������
class IngredientBuilder : public Builder<Ingredient>
{
public:

	// ����������� �� ���������
	IngredientBuilder();

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// �������� ������ ������� 
	int getEffectsTableSize();

	// ������ ��� ������� ��������
	EffectsTable* getEffectsTable();

	// ������� ����������
	void buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex);

	// ������� ���������� �� �����
	void buildIngredient(string ingredientName, EffectsTable* effectsTable);

	// �������� ������
	void addEffect(int effectId);

	// ��������� ������ id ��������
	void fillEffectId();

#pragma region �������

	// ������ ���
	void setName(string name);

	// ������ ���
	void setNameFromListRandomly(int lastIngredientNameIndex);

	// ������ ����
	void setPrice(int price);

	// ������ ���� ��������
	void setPriceRandomly();

	// ������ ����������� �������
	void setEffects(int& lastEffectIndex);

	// ������ ����������� �������� ��� �������� � ����������� �������
	void setEffectsRandomly();

#pragma endregion �������

private:

	// ������� ��������
	EffectsTable* effectsTable;

	// ������� ��� �������
	string chooseIngredientName(int lastIndex);

	// ������ ���� ������������
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// ������ id ��������
	vector<int> effectsId;
};