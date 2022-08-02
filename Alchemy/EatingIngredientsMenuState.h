#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
//#include "AlchemicalMenuState.h"
#include "ServiceFunctions.h"

class EatingIngredientsMenuState : public MenuState
{
public:

	EatingIngredientsMenuState();

	EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);
	
	//~EatingIngredientsMenuState() override;

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

	//void printErrorWrongIdAndMakeChoiceAgain(int& ingredientId, int yCoord);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	bool wasClosedEffect(int ingredientId);

	//void printErrorWrongEffectAndMakeChoiceAgain(int& ingredientId, int yCoord);
};

