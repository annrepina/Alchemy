#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"

#define NUMBER_OF_INGREDIENTS		100		// ���-�� ������������

#define MIN_PRICE					4.f		// ����������� ���� �����������
#define MAX_PRICE					135.f		// ������������ ���� �����������

class IngredientBuilder
{
public:

	// ����������� �� ���������
	IngredientBuilder();

	// ����������
	~IngredientBuilder();

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	void buildIngredient(int lastIndex, int& lastEffectIndex);

	// �������� ������
	void addEffect(int effectId);

	// �������� ���������
	Ingredient* getResult();

private:

	// ��������� �����������
	Ingredient* ingredient;

	EffectsTable* effectsTable;

	// ������� ��� �������
	string chooseIngredientName(int lastIndex);

	// ������������� ���� �����������
	int generatePrice();

#pragma region �������

	// ������ ���
	void setName(string name);

	// ������ ����
	void setPrice(float price);



#pragma endregion �������

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();

	// ������ ���� ������������
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	//// ������ ���� ��������
	//static string listOfEffectsNames[55];
};

