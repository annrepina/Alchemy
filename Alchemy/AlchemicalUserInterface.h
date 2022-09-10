#pragma once
#include "UserInterface.h"
//#include "Alchemist.h"
//#include "IngredientBuilder.h"
#include "AlchemyLogicBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"
#include "IObserver.h"
#include "PotionTablePrinter.h"
#include "AlchemyLogicWriter.h"
#include "AlchemyLogicReader.h"

// ����������
#define TITLE_Y_COORD					1		// ���������� Y ������� ��� ������ �������� ���������
#define EXIT_Y_COORD					2		// ���������� Y ������ ������
#define Y_COORD_AFTER_ALCHEMIST			8		// ���������� Y ����� ������ ��������
#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������
#define PAGE_Y_COORD					44		// ���������� Y ���� ������� ������� - ��������� �� 6


// �������� �� ���������
#define FIRST_PAGE						1		// ������ �������� �������
#define DEFAULT_NUMBER_OF_COLUMN		1		// ����� ������� �� ��������� ��� ������ � ��������

#define MAX_INT							2147483647	// ����� ������� ����� int 

#define TWO_LINES						2		// ��� �������

class AlchemicalUserInterface : public UserInterface
{
public:

	// ����������� �� ���������
	AlchemicalUserInterface();

	// ������ �������� ����� ���������
	void launchProgram() override;

#pragma region �������

	// �������� ��������� ���������� Y
	int getBoundaryYCoord();

	bool getExitFlag();

	AlchemyLogic* getAlchemyLogic();

	IngredientsTablePrinter* getIngredientsTablePrinter();

	PotionTablePrinter* getPotionTablePrinter();

#pragma endregion �������

#pragma region C������

	// ���������� ���������
	void setState(MenuState* state);

	void setExitFlag(bool exit);

#pragma endregion C������

	enum class TableCode
	{
		IngredientTable,
		PotionTable
	};

	// ������ ������� ������ � �����
	void printTablePagesInLoop(TableCode code, int& page);

	void printTablePagesInLoopWhileSorting(vector<vector<string>> content, TableCode code, int& page, int numberOfColumn, bool orderOfSorting);

	// ������ ������� ������ � ���� ����������, ������� ���������� � �����
	void printTableWithAvailableToUserElements(TableCode code, int& page);

	// ������ ������� ������ �������� ������� (������ ��, ��� ���� � �����)
	void printFirstTablePage(TableCode code);

	// ������� Id �� �������
	int chooseId(/*string strChoice, */TableCode code);

	// ������� Id �� ��������� ���������
	int chooseIdFromAvailableElements(string strChoice, TableCode code);

	// ������ ���-�� ����������� ��� �����
	int chooseNumber(string strChoice, int yCoord);

	void chooseExit();

	void chooseColumnAndOrderOfSorting(int& numberOfColum, bool& orderOfSorting, TableCode code);

	void chooseColumnForFiltration(int& numberOfColumn, TableCode code);

private:

	// ��������� - �������
	AlchemyLogic* alchemyLogic;

	// ��������� ��� ������������ ���������
	AlchemyLogicBuilder* alchemyLogicBuilder;

	// ������ ��� ������ �������
	AlchemyLogicWriter* alchemyLogicWriter;

	// ����� ��� ������ �������
	AlchemyLogicReader* alchemyLogicReader;

	// ������� ��� ������ ������� ������������
	IngredientsTablePrinter* ingredientsTableprinter;

	PotionTablePrinter* potionTablePrinter;

	// ��������� ����
	MenuState* state;

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	// ��������� ���������� Y ��� ���������� ���������
	int boundaryYCoord;

	// ���� ��� ������
	string pathForWriting;

	// ��������� ��������� �������
	void setAlchemyLogic();

	bool isFileForReadingEmpty();

#pragma region �������� ����������

	// �������� �������� ����
	string mainMenuTitle;

	// �������� ����������
	string instructionsMenuTitle;

	// �������� ���� �������
	string alchemicalMenuTitle;

	// �������� ���� ������� ������������
	string buyingIngredientsMenuTitle;

	// �������� ���� ������ �� ����� ������� ������������
	string buingFaultMenuTitle;

#pragma endregion �������� ����������

	// ������� �������� �������
	void choosePage(int page, TableCode code);

	void choosePageWhileSorting(vector<vector<string>> content, int page, TableCode code, int numberOfColumn, bool orderOfSorting);

	// ������� �������� ������� ����� ��������� ���������
	void choosePageFromAvailableContent(int page, TableCode code);

#pragma region �������� ���� ��� ������

	// ��������� �������������� ������� � ������ � ������� �������� � �������
	bool checkHorizontalArrowChoice(int& page, TableCode code, int keyCode);

	// ��������� �������������� ������� � ������ � ������� �������� � �������
	bool checkHorizontalArrowChoice(int contentSize, int& page, TableCode code, int keyCode);

	// ��������� �������������� ������� � ������ � ������� ������� �� ����� ����������
	bool checkHorizontalArrowChoice(int& numberOfColums, int keyCode, TableCode code);

	// ��������� ������������ ��������� � ������ ������ ������� ����������
	bool checkVerticalArrowChoice(bool& orderOfSorting, int keyCode, TableCode code);

#pragma endregion �������� ���� ��� ������

	// ������� � ������� ��� ����� ������ ��������
	void eraseScreenAfterAlchemist();

	void writeAlchemyLogic();

#pragma region ������ ������

	// �������� ��������� ���������
	void printTitle() override;

	// �������� "������" ������ ESC
	void printExitButton() override;

	// ������ �������� ���� � �����
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	// ������ ��������
	void printBye() override;

	// ������ ���� ��� ��������
	void printAlchemist();

	// ������ �������� ����
	void printMenuTitle(string title);

	// ������ ���� ������ ��������
	void printPageMenu(int page);

#pragma endregion ������ ������

#pragma region ���������

	// ����������� ����� ��������
	bool isPageChoiceFalse(int key);

	// ������������ ����� ������� ��� ����������� ����������
	bool isColumnAndOrderChoiceFalse(int key);

#pragma endregion ���������

};