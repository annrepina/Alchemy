#pragma once
//#include <string>
//#include <conio.h>
//#include <functional>
//#include "Formatting.h"
//#include "KeyBoard.h"
#include "Alchemist.h"
#include "IngredientsTable.h"
#include "PotionTable.h"
#include "EffectsTable.h"
#include "IngredientBuilder.h"
#include "PotionBuilder.h"
#include "ServiceFunctions.h"

//using namespace std;
//
//using std::placeholders::_1;

//// ����������
//#define TITLE_Y_COORD			1		// ���������� Y ������� ��� ������ �������� ���������
//#define Y_COORD_AFTER_TITLE		4		// ���������� Y ����� ������� ���������
//
//// ���� ������
//#define VK_1					0x31	// ������� 1
//#define VK_2					0x32	// ������� 2
//#define VK_NUMPAD1				0x61	// ������� �������� ���������� 1
//#define VK_NUMPAD2				0x62	// ������� �������� ���������� 2
//#define VK_ESCAPE				0x1B	// ������� ESC
//#define VK_RETURN				0x0D	// ������� Enter

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

	void setPotionTable(PotionTable* potionTable);

	void setAlchemist(Alchemist* alchemist);

#pragma endregion �������

#pragma region �������

	// ������ ��� ��������
	Alchemist* getAlchemist();

	// ������ ��� ������� ��������
	EffectsTable* getEffectsTable();

	IngredientsTable* getIngredientsTable();

	PotionTable* getPotionTable();

#pragma endregion �������

	// ����������� �������� ���. ���-�� ����������� �� ������
	bool tryBuyIngredientFromList(int id, int number);

	bool tryAddNewIngredientToTable(string ingredientName);

	void checkPotion(Potion* potion);

	// ������ �����
	Potion* createPotion(Ingredient* firstIngredient, Ingredient* secondIngredient);

	void sellIngredient(int ingredientId, int numberOfIngredient);

	void decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient);

	void eatIngredient(int ingredientId);

	//vector<int> findEqualEffects(int firstIngredientId, int secondIngredientId);

	//// ������� ����� � ��������� ��� � �������
	//void addPotion(int effectId);

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

	//// ������� ����� ����������
	//Ingredient* createNewIngredient(string ingredientName);
};

