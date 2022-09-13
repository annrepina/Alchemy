#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING		1	// ���������� ��������� ���-�� ����� ��� ������� 

// ��������� ���� - ������� �����
class SellingPotionsMenuState : public MenuState
{
public:

	// ����������� �� ���������
	SellingPotionsMenuState();

	// ����������� � ����������
	SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (SellingPotionsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (SellingPotionsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	// �������� ���������� id �� ������� ����� id
	void checkPotionId(int& potionId);

	// �������� ���������� ���������� ����� �� ������������
	void checkNumberOfPotion(int& numberOfPotion, int potionId);

#pragma region ������ ������

	// ������ ����
	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);

	// ������ ������ � ������������ ������ ����� �����
	void printErrorAndMakeChoiceAgain(int& potionId, int yCoord);

	// ������ ������ � ������������ ������ ����� �����
	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& potionId);

#pragma region ������ ������
};