#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING		1	// ���������� ��������� ���-�� ������������ ��� ������� 

class SellingIngredientsMenuState : public MenuState
{
public:

	SellingIngredientsMenuState();

	SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingIngredientsMenuState() override;

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
	map<int, function<MenuState* (SellingIngredientsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (SellingIngredientsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);

	//// ������ ������ id � ���������� ���������
	//int printChoiceId(int yCoord, int xCoord);

	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);


	// �������� ���������� id �� ������� ����� id
	void checkIngredientsId(int& ingredientId);

	void checkNumberOfIngredient(int& numberOfIngredient, int ingrdientId);

	//void decreaseNumberOfIngredients(int igredientId);

};

