#pragma once
#include "UserInterface.h"
//#include "Alchemist.h"
//#include "IngredientBuilder.h"
#include "AlchemyLogicBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"
#include "IObserver.h"

// ����������
#define TITLE_Y_COORD					1		// ���������� Y ������� ��� ������ �������� ���������
#define EXIT_Y_COORD					2		// ���������� Y ������ ������
#define Y_COORD_AFTER_ALCHEMIST			8		// ���������� Y ����� ������ ��������
#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������
#define PAGE_Y_COORD					37		// ���������� Y ���� ������� �������
//#define Y_COORD_AFTER_MENU_TITLE_1		9		// ���������� Y ������ ����� ������ ��������� ����
//#define Y_COORD_AFTER_MENU_TITLE_2		10		// ���������� Y ������ ����� ������ ��������� ����
//#define Y_COORD_AFTER_MENU_TITLE_3		11		// ���������� Y ������ ����� ������ ��������� ����
//#define Y_COORD_AFTER_MENU_TITLE_4		12		// ���������� Y ��������� ����� ������ ��������� ����
//#define Y_COORD_AFTER_MENU_TITLE_4		12		// ���������� Y ��������� ����� ������ ��������� ����
//#define STANDARD_CURSOR_X_COORD			0		// ����������� ���������� X ������� 


// ���-��
//#define NUMBER_OF_MAIN_MENU_ITEMS		2		// ���-�� ������� � ������� ����
//#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	7		// ���-�� ������� � ������������ ����
//#define NUMBER_OF_BUYING_MENU_ITEMS		3		// ���-�� ������� � ���� ������� ������������

#define FIRST_PAGE						1		// ������ �������� �������

#define MAX_INT							2147483647	// ����� ������� ����� int 

#define TWO_LINES						2		// ��� �������

class AlchemicalUserInterface : public UserInterface
{
public:

	// ����������� �� ���������
	AlchemicalUserInterface();

	// ������ �������� ����� ���������
	void launchMainLoop() override;

#pragma region �������

	// �������� ��������� ���������� Y
	int getBoundaryYCoord();

	bool getExitFlag();

	AlchemyLogic* getAlchemyLogic();

#pragma endregion �������

#pragma region C������

	// ���������� ���������
	void setState(MenuState* state);

	void setExitFlag(bool exit);

#pragma endregion C������

	enum TableCode
	{
		IngredientTable,
		PotionTable
	};

	// ������ ������� ������ � �����
	void printTablePagesInLoop(TableCode code, int& page);

	// ������� Id �� �������
	int chooseId(string strChoice, TableCode code);

	// ������ ���-�� ����������� ��� �����
	int chooseNumber(string strChoice, TableCode code, int yCoord);

	//// ����������� �������� ���. ���-�� ����������� �� ������
	//bool tryAddIngredientFromList(int id, int number);

private:

#pragma region ����

	//// ���� ����
	//enum MenuCode
	//{
	//	MainMenu1, 
	//	AlchemicalMenu,
	//	InstructionsMenu,
	//	BuyingIngredientsMenu,
	//	BuyingFaultMenu
	//};

	//// ���� ������� � ������� ����
	//enum MainMenuCode
	//{
	//	DoAlchemy = MAIN_MENU_Y_COORD,
	//	ReadInstructions
	//};

	//// ���� ������������� ����
	//enum AlchemicalMenuCode
	//{
	//	MakingPotions = MAIN_MENU_Y_COORD,
	//	BuyingIngredients,
	//	SellingIngredients,
	//	EatingIngredients,
	//	SellingPotions,
	//	WorkingWithTables, 
	//	AlcReturn
	//};

	//// ���� ���� ����������
	//enum InstructionsMenuCode
	//{
	//	InstrReturn = MAIN_MENU_Y_COORD,
	//	Exit
	//};

	//// ���� ���� ������� ������������
	//enum BuyingIngredientsMenuCode 
	//{
	//	ChooseFromList = MAIN_MENU_Y_COORD,
	//	CreateNewIngredient
	//};

	//// ���� ���� ������ �� ����� ������� ������������
	//enum BuyingFaultMenuCode
	//{
	//	�hooseAnotherIngredient = MAIN_MENU_Y_COORD, 
	//	ChangeNumberOfIngredient
	//};



#pragma endregion 

	// ��������� - �������
	AlchemyLogic* alchemyLogic;

	// ��������� ��� ������������ ���������
	AlchemyLogicBuilder* alchemyLogicBuilder;

	// ������ ��� ��������� �������
	AlchemyProgramParser* alchemyProgramParser;

	// ������� ��� ������ ������� ������������
	IngredientsTablePrinter* ingredientsTableprinter;

	// ��������� ����
	MenuState* state;

	// ��������� ��������� �������
	void setAlchemyLogic();

	//// ������ ����� - ������� �������� ����
	//static string listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// ������������� ������ ��������� � "������" �������� ����
	//map <int, string> mainMenu;

	//// ������ ����� - ������� ���� �������
	//static string listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS];

	//// ������������� ������ ��������� � "������" ���� �������
	//map <int, string> alchemicalMenu;

	//// ������ ����� - ������� ���� ����������
	//static string listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// ������������� ������ ��������� � "������" ���� ����������
	//map <int, string> instructionsMenu;

	//// ������ ����� - ������� ���� ������� ������������
	//static string listOfBuyingIngredientsMenuItems[NUMBER_OF_BUYING_MENU_ITEMS];
	//
	//// ������������� ������ ��������� � "������" ���� ������� ������������
	//map<int, string> buyingIngredientsMenu;

	//// ������ ����� - ������� ���� ������ ��� ������� ������������
	//static string listOfBuyingFaultMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// ������������� ������ ��������� � ������� ���� ������ �� ����� ������� ������������
	//map <int, string> buyingFaultMenu;

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	// ��������� ���������� Y ��� ���������� ���������
	int boundaryYCoord;

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

	//// ������� �������
	//void chooseMenuItem(map <int, string> menu);

	// ������� �������� �������
	void choosePage(int page, TableCode code);

	//// ������� ����� ������ ����
	//void makeChoice(bool& innerExitFlag);

	//void makeChoice();

#pragma region �������� ���� ��� ������

	//// �������� ������ � ������� ����
	//void checkMainMenu(bool& innerExitFlag);

	//// �������� ������ � ���� ����������
	//void checkInstructionsMenu(bool& innerExitFlag);

	//// �������� ����� ���� � ���� �������
	//void checkAlchemicalMenu(bool& innerExitFlag);

	//// �������� ������ ������ � ���� ������� ������������
	//void checkBuyingIngredientsMenu(bool& innerExitFlag);

	//// �������� ������ ������ � ���� ������ ��� ������� ������������ �� ������ 
	//void checkBuyingFaultMenu();

	// ��������� �������������� �������
	bool checkHorizontalArrowChoice(int& page, TableCode code, int keyCode);

#pragma endregion �������� ���� ��� ������

	//// ���������� ��������
	//void doAlchemy();

	//// ������� ������������
	//void buyIngredients();

	//// ������� ������������ �� ���������� ������
	//void buyIngredientsFromList();

	// ������� � ������� ��� ����� ������ ��������
	void eraseScreenAfterAlchemist();

	//// ��������� ��� ����
	//void fillAllMenu();

#pragma region ������ ������

	// �������� ��������� ���������
	void printTitle() override;

	// �������� "������" ������ ESC
	void printExitButton() override;

	// ������ �������� ���� � �����
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	//// ������ ����������
	//void printInstructions() override;

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

#pragma endregion ���������

};