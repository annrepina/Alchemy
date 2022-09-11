#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

// ��������� ���� - �������� ������������
class EatingIngredientsMenuState : public MenuState
{
public:

	EatingIngredientsMenuState();

	EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (EatingIngredientsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (EatingIngredientsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void checkIngredientsId(int& ingredientId);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	bool wasClosedEffect(int ingredientId);
};