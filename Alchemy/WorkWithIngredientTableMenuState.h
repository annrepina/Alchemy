#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS						3		// 3 ���������� ������ ����

#define DEFAULT_NUMBER_OF_COLUMN				1		// ����� ������� �� ��������� ��� ������ � ��������
#define NUMBER_OF_SEARCHING_QUERIES				9		// ���-�� ��������� �������� ��� ������� � �������������

#define X_COORD_FOR_FILTER_ITEMS				20		// ���������� ��� ������ ������� ���� �� ����� ����������
#define	GAP_BETWEEN_FILTER_AND_VALUE			5		// ����������� ����� �������� � ��������

// ���������� ������� �������� �� ����������� �� Y
#define FILTER_NAME_3								3		// ������ �� �����
#define FILTER_EFFECT_6								6		// ������ �� ������� 1
#define FILTER_EFFECT_7								7		// ������ �� ������� 2

#define COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE	2		// ������� � ������������ ����� ���������� � ��������� ��� ����������

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
	int numberOfColumnforSorting;

	// ������� ����������
	bool orderOfSorting;

	// ���������� � ��� ������ ������ ��� ����������
	int xCoordForFilterValue;

	IngredientsTablePrinter* ingredientTablePrinter;

	// ��������� �������
	vector<string> searchingQueries;

	// ��������� ��������� ������
	void addSearchingQuery(string query, int numberOfQuery);

#pragma region �������

	// ������ ������ ��������� �������� �� ���������
	void setSearchingQueriesDefault();

	// ������ ������� ��� ������
	virtual void setContent();

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	void setListOfColumnTitles();

#pragma endregion �������

	// �������� ������� ������� - ����
	vector<vector<string>> initialContent;

	// ������� ����� ����������
	vector<vector<string>> contentAfterSortingAndResearch;

	// ������ ����������� ����
	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	// ������� ��� ����������
	map<int, string> columnForFiltration;

	vector<string> listOfColumnForFiltration;

	int longestColumnSize;

	virtual void printMenuItems(vector<string> listOfItems);

	virtual void printFilterItems(vector<string> listOfItems);

	//void chooseMenuItem() override;

	void chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting);

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

	// ��������� ����������
	virtual void launchSorting();

	virtual void launchFilterMenu();

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

