#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"
#include "PotionBuilder.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING		2	// ���������� ��������� ���-�� ������������ ��� ���������� 


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

	// ��������� �����
	PotionBuilder* potionBuilder;

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

	void printMenu(string choiceFirstIngredient, string choiceSecondIngredient);

	// ������ ������ id
	int printChoiceId(int yCoord, int xCoord);

	// ��������� ���-�� ������������
	void decreaseNumberOfIngredients(int firstIngredientId, int secondIngredientId);

	// �������� ��������� id �� ����������
	void checkIngredientsId(int &firstIngredientId, int &secondIngredientId);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	void checkIdForEquality(int& firstIngredientId, int secondIngredientId, int YCoord);

	//// �������� ��� ������ �� ����
	//void exitMenu();

};

