#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"

#define NUMBER_OF_INGREDIENTS		100		// ���-�� ������������

//#define MIN_PRICE					4		// ����������� ���� �����������
//#define MAX_PRICE					135		// ������������ ���� �����������

class IngredientBuilder
{
public:

	// ����������� �� ���������
	IngredientBuilder();

	// ����������
	~IngredientBuilder();

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// �������� ������ ������� 
	int getEffectsTableSize();

	// ������ ��� ������� ��������
	EffectsTable* getEffectsTable();

	// ������� ����������
	void buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex);

	// �������� ������
	void addEffect(int effectId);

	// ��������� ������ ���� ��������
	void fillEffectId();

	// �������� ���������
	Ingredient* getResult();

private:

	// ��������� �����������
	Ingredient* ingredient;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������� ��� �������
	string chooseIngredientName(int lastIndex);

#pragma region �������

	// ������ ���
	void setName(string name);

	// ������ ����
	void setPrice(int price);

#pragma endregion �������

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();

	// ������ ���� ������������
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// ������ ���� ��������
	vector<int> effectsId;

	// ���-�� ������������
	int numberOfIngredients;
};

