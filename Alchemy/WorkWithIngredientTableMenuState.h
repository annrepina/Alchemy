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

	// ����� �������, �� �������� ���������
	int numberOfColumn;

	// ������� ����������
	bool orderOfSorting;

	IngredientsTablePrinter* ingredientTablePrinter;

	// ������ ������� ��� ������
	virtual void setContent();

	// �������� ������� ������� - ����
	vector<vector<string>> initialContent;

	// ��������� ����� ������ � ������
	vector<vector<string>> contentAfterSortingAndSearch;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	void printMenuItems() override;

	void chooseMenuItem() override;

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ���������� �������� ���������� ��� ������
	int defineOperation();

	enum class OperationCode
	{
		Sorting,
		Search
	};

	virtual void workWithTable(OperationCode operationCode);

	virtual void sortData();

private:

	// ������ ������ ���������
	void setListOfStates() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode) override;
};

