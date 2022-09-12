#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"
#include "PotionBuilder.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING		2	// ���������� ��������� ���-�� ������������ ��� ���������� 

// ��������� ���� - �������� �����
class CreatingPotionsMenuState : public MenuState
{
public:

	// ����������� �� ���������
	CreatingPotionsMenuState();

	// ����������� � �����������
	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

private:

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (CreatingPotionsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (CreatingPotionsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

#pragma region ������ ������

	// ������ ����
	void printMenu(string choiceFirstIngredient, string choiceSecondIngredient, string choiceNumberOfIngredients);

	// ������ ������, ����� ������������ ������ ����� �����
	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	// ������ ������, ����� ������������ ������ ����� �����
	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	// ������ ������ � ����������, ����� ������������ ������ ����� �����
	void printErrorAboutNumberAndMakeChoiceAgain(int ingredientId, int previousNumber, int& numberOfIngredients, int yCoord);

	// ������ ������ � ����������, ����� ������������ ������ ����� �����
	void printErrorAboutNumberAndMakeChoiceAgain(int yCoord, string textOfError, int& numberOfIngredients);

#pragma endregion ������ ������

	// ��������� ���-�� ������������
	void decreaseNumberOfIngredients(int firstIngredientId, int secondIngredientId, int number);

#pragma region ������ ��������

	// �������� ��������� id �� ����������
	void checkIngredientsId(int &firstIngredientId, int &secondIngredientId);

	// ��������� ���� �� ����� ���-�� ������������ � ������������
	void checkNumberOfIngredients(int firstIngredientId, int secondIngredientId, int &numberOfPotion);

	// �������� ��������� id ������������ �� ��������� 
	void checkIdForEquality(int& firstIngredientId, int secondIngredientId, int YCoord);

#pragma endregion ������ ��������
};

