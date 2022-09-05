#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS						3		// 3 ���������� ������ ����

#define DEFAULT_NUMBER_OF_COLUMN				1		// ����� ������� �� ��������� ��� ������ � ��������
#define NUMBER_OF_INGREDIENT_TABLE_COLUMNS		6		// ���-�� ������ � ������� � �������������

#define X_COORD_FOR_FILTER_ITEMS				20		// ���������� ��� ������ ������� ���� �� ����� ����������
#define	GAP_BETWEEN_FILTER_AND_VALUE			5		// ����������� ����� �������� � ��������

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

	// ���������� � ��� ������ ������ ��� ����������
	int xCoordForFilterValue;

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

	int longestColumnSize;

	virtual void printMenuItems(vector<string> listOfItems);

	virtual void printFilterItems(vector<string> listOfItems);

	//void chooseMenuItem() override;

	void chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting);

	//// ������� ������� ��� ����������
	//void chooseFilterColumn();

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

	// ��������� ����� ������� ����� ���������� (�������� �������)
	virtual int calculateLongestFIlteringItem();

	// ������� ������� �������� ���������� ��� ������� � �������?
	virtual bool isStringColumn(int numberOfColumn);

	int calculateNumberOfColumnForFiltration();

private:

	// ������ ������ ���������
	void setListOfStates() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items);
};

