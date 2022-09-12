#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS							3		// 3 ���������� ������ ����

#define DEFAULT_NUMBER_OF_COLUMN					1		// ����� ������� �� ��������� ��� ������ � ��������
#define NUMBER_OF_SEARCHING_QUERIES					9		// ���-�� ��������� �������� ��� ������� � �������������

#define X_COORD_FOR_FILTER_ITEMS					20		// ���������� ��� ������ ������� ���� �� ����� ����������
#define	GAP_BETWEEN_FILTER_AND_VALUE				5		// ����������� ����� �������� � ��������

// ���������� ������� �������� �� ����������� �� Y
#define FILTER_NAME_3								3		// ������ �� �����
#define FILTER_EFFECT_6								6		// ������ �� ������� 1
#define FILTER_EFFECT_7								7		// ������ �� ������� 2

#define COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE	2		// ������� � ������������ ����� ���������� � ��������� ��� ����������

class AlchemicalUserInterface;

// ��������� ���� - ������ � �������� ������������
class WorkWithIngredientTableMenuState : public MenuState
{
public:

	// ����������� �� ���������
	WorkWithIngredientTableMenuState();

	// ����������� � ����������
	WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

protected:

	// ����� �������, �� �������� ���������
	int numberOfColumnforSorting;

	// ������� ����������
	bool orderOfSorting;

	// ���������� � ��� ������ ������ ��� ����������
	int xCoordForFilterValue;

	// ������� ������������
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

	// ������ ������ ���������� ������� ����
	void setListOfInnerMenuItems();

	// ������ ����� �������� �������� ��� ��������
	virtual void setListOfColumnFilters();

	// ������ ��������� ����
	virtual void setFields();

#pragma endregion �������

	// �������� ������� ������� - ����
	vector<vector<string>> initialContent;

	// ������� ����� ����������
	vector<vector<string>> contentAfterSortingAndResearch;

	// ������ ����������� ���� � ������������ �� Y
	map<int, string> innerMenuItems;

	// ������ ������� ����������� ����
	vector<string> listOfInnerMenuItems;

	// ������� ��� ���������� � ���������� �� Y
	map<int, string> columnForFiltration;

	// ������ �������� ������� ��� ����������
	vector<string> listOfColumnFilters;

	// ����� ������ �������� �������� ������� ��� �������
	int longestFilterSize;

	// ������ ������� ����
	virtual void printMenuItems(vector<string> listOfItems);

	// ������ ������� ����������
	virtual void printFilterItems(vector<string> listOfItems);

	// �������� � ��������
	virtual void workWithTable();

	// ������� ����� ����
	void chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting);

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ���������� �������� ���������� ��� ������
	int defineOperation();

	// ���� ��������
	enum class OperationCode
	{
		Sorting,
		Search
	};

	// �������� � �������� - ����������
	virtual void workWithTable(OperationCode operationCode);

	// ��������� ���� ����������
	virtual void launchSortingMenu();

	// ��������� ����������
	virtual void sortData();

	// ��������� ���� ����������
	virtual void launchFilterMenu();

	// ����������� ������
	virtual void filterData();

	// ��������� ����� ������� ����� ���������� (�������� �������)
	virtual int calculateLongestFIlteringItem();

	// ������� ������� �������� ���������� ��� ������� � �������?
	virtual bool isStringColumn(int numberOfColumn);

	// ���������� �� ����� ������� ����������
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

	// ��������� ����� ������������ ��������� �� ������������
	void checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items);
};