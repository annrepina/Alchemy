#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS				3		// 3 ���������� ������ ����

#define DEFAULT_NUMBER_OF_COLUMN		1		// ����� ������� �� ��������� ��� ������ � ��������

class AlchemicalUserInterface;

class WorkWithIngredientTableMenuState : public MenuState
{
public:

	WorkWithIngredientTableMenuState();

	WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

	// ������ ����
	void printMenu() override;

protected:



private:

	enum class OperationCode
	{
		Sorting,
		Search
	};

	// ����� �������, �� �������� ���������
	int numberOfColumn;

	// ������� ����������
	bool orderOfSorting;

	// �������� ������� ������� - ����
	vector<vector<string>> initialContent;

	// ��������� ����� ������ � ������
	vector<vector<string>> contentAfterSortingAndSearch;

	IngredientsTablePrinter* ingredientTablePrinter;

	// �������� ��������� ���������

	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// ������ ������� ��� ������
	void setContent();

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void printMenuItems() override;

	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode) override;

	void chooseMenuItem() override;

	void setListOfInnerMenuItems();

	// ���������� �������� ���������� ��� ������
	int defineOperation();

	void workWithTable(OperationCode operationCode);
};

