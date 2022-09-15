#pragma once
#include "Alchemist.h"
#include "IngredientsTable.h"
#include "PotionTable.h"
#include "EffectsTable.h"
#include "IngredientBuilder.h"
#include "PotionBuilder.h"
#include "ServiceFunctions.h"

#define ASCENDING_ORDER_OF_SORTING		true	// ������� ���������� �� �����������
#define DESCENDING_ORDER_OF_SORTING		false	// ������� ���������� �� ��������

// �����, �������������� ������ ������������
class AlchemyLogic
{
public:

	// ����������� �� ���������
	AlchemyLogic();

#pragma region �������

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ������ ��� ������� ������������
	void setIngredientsTable(IngredientsTable* ingredientsTable);

	// ������ ��� ������� ������
	void setPotionTable(PotionTable* potionTable);

	// ������ ��� ��������
	void setAlchemist(Alchemist* alchemist);

#pragma endregion �������

#pragma region �������

	// ������ ��� ��������
	Alchemist* getAlchemist();

	// ������ ��� ������� ��������
	EffectsTable* getEffectsTable();

	// ������ ��� ������� ������������
	IngredientsTable* getIngredientsTable();

	// ������ ��� ������� ������
	PotionTable* getPotionTable();

#pragma endregion �������

	// ����������� �������� ���. ���-�� ����������� �� ������
	bool tryBuyIngredientFromList(int id, int number);

	// ����������� �������� ����� ���������� � �������
	bool tryAddNewIngredientToTable(string ingredientName);

	// ��������� �����, ���� �� ����� ��� � �������
	void checkPotion(Potion* potion, vector<Potion*> &potions);

	// ����� ����������?
	bool isPotionsAreEqual(Potion* potion1, Potion* potion2);

	// ������ �����
	Potion* createPotion(Ingredient* firstIngredient, Ingredient* secondIngredient);

	// ������� ����������
	void sellIngredient(int ingredientId, int numberOfIngredient);

	// ������� �����
	void sellPotion(int potionId, int numberOfPotion);

	// ��������� ���-�� �����������
	void decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient);

	// ��������� ���-�� �����
	void decreaseNumberOfPotion(int potionId, int numberOfPotion);

	// ������ ����������
	void eatIngredient(int ingredientId);

	// ���������� ����� ������ ���������
	void sortStringData(vector<string>* tableData, int numberOfColumn, bool order, int size);

	// ���������� ����� ������ ��������
	void sortDigitData(vector<string>* tableData, int numberOfColumn, bool order, int size);

private:

	// ������� (������������)
	Alchemist* alchemist;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������� ������������
	IngredientsTable* ingredientsTable;

	// ������� �����
	PotionTable* potionTable;

	// ��������� ���� �� �������� �������� ������������ ��� � �������
	bool hasSuchIngredientName(string ingredientName);

	// ������ �� ������� ����� �����, ���� �� �� ���������� Id ����� �����
	int hasSuchPotion(Potion* potion);
};