#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS						3		// 3 ���������� ������ ����

#define DEFAULT_NUMBER_OF_COLUMN				1		// ����� ������� �� ��������� ��� ������ � ��������
#define NUMBER_OF_INGREDIENT_TABLE_COLUMNS		6		// ���-�� ������ � ������� � �������������

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

	// ��������� �������
	vector<string> searchingQueries;

	// ������ ������ ��������� �������� �� ���������
	void setSearchingQueriesDefault();

	// ������ ������� ��� ������
	virtual void setContent();

	// �������� ������� ������� - ����
	vector<vector<string>> initialContent;

	// ��������� ����� ������ � ������
	vector<vector<string>> contentAfterSortingAndSearch;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	void setListOfColumnTitles();

	// ������ ����������� ����
	map<int, string> innerMenuItems;

	// ������� ��� ����������
	map<int, string> columnForFiltration;

	vector<string> listOfColumnTitles;

	vector<string> listOfInnerMenuItems;

	void printMenuItems(vector<string> listOfItems);

	//void chooseMenuItem() override;

	void chooseMenuItem(vector<string> listOfItems);

	// ������� ������� ��� ����������
	void chooseFilterColumn();

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

	virtual void filterData();

private:

	// ������ ������ ���������
	void setListOfStates() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode, vector<string> items);
};

