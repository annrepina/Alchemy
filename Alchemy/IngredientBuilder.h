#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Builder.h"

#define NUMBER_OF_INGREDIENTS		100		// ���-�� ������������

//#define MIN_PRICE					4		// ����������� ���� �����������
//#define MAX_PRICE					135		// ������������ ���� �����������

class IngredientBuilder : public Builder<Ingredient>
{
public:

	// ����������� �� ���������
	IngredientBuilder();

	//// ����������
	//~IngredientBuilder();

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

	// ��������� ������ id ��������
	void fillEffectId();

#pragma region �������

	// ������ ���
	void setName(string name);

	// ������ ����
	void setPrice(int price);

#pragma endregion �������

private:

	// ������� ��������
	EffectsTable* effectsTable;

	// ������� ��� �������
	string chooseIngredientName(int lastIndex);

	//// �������� �� ��������� ���������
	//void reset();

	//// ������� ������
	//void clear();

	// ������ ���� ������������
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// ������ id ��������
	vector<int> effectsId;
};

