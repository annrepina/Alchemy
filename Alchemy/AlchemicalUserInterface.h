#pragma once
#include "UserInterface.h"
//#include "Alchemist.h"
//#include "IngredientBuilder.h"
#include "AlchemyProgramBuilder.h"
#include "IngredientsTablePrinter.h"
//#include "AlchemyProgram.h"

// ����������
#define TITLE_Y_COORD					1		// ���������� Y ������� ��� ������ �������� ���������
#define EXIT_Y_COORD					2		// ���������� Y ������ ������
#define Y_COORD_AFTER_ALCHEMIST			8		// ���������� Y ����� ������ ��������
#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������
//#define INSTRUCTIONS_Y_COORD			10
#define Y_COORD_AFTER_MENU_TITLE		9		// ���������� Y ����� ������ ��������� ����
#define STANDARD_CURSOR_X_COORD			0		// ����������� ���������� X ������� 



// ���-��
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// ���-�� ������� � ������� ����
#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	6		// ���-�� ������� � ������������ ����

class AlchemicalUserInterface : public UserInterface
{
public:

	// ����������� �� ���������
	AlchemicalUserInterface();

	// ������ �������� ����� ���������
	void launchMainLoop() override;

private:

	// ���� ����
	enum MenuCode
	{
		MainMenu, 
		AlchemicalMenu,
		InstructionsMenu,
		BuyingIngredientsMenu
	};

	// ���� ������� � ������� ����
	enum MainMenuCode
	{
		DoAlchemy = MAIN_MENU_Y_COORD,
		ReadInstructions
	};

	enum AlchemicalMenuCode
	{
		MakingPotions = MAIN_MENU_Y_COORD,
		BuyingIngredients,
		SellingIngredients,
		EatingIngredients,
		SellingPotions,
		WorkingWithTables
	};

	enum InstructionsMenuCode
	{
		Return = MAIN_MENU_Y_COORD,
		Exit
	};

	enum BuyingIngredientsMenuCode 
	{
		ChooseFromList = MAIN_MENU_Y_COORD,
		CreateNewIngredient
	};

	// ��������� - �������
	AlchemyProgram* alchemyProgram;

	// ��������� ��� ������������ ���������
	AlchemyProgramBuilder* alchemyProgramBuilder;

	// ������ ��� ��������� �������
	AlchemyProgramParser* alchemyProgramParser;

	// �������
	IngredientsTablePrinter* printer;

	// ��������� ��������� �������
	void setAlchemyProgram();

	// ������� (������������)
	//Alchemist* alchemist;

	//// ��������� ������������
	//IngredientBuilder* ingredientBuilder;

	// ������ ����� - ������� �������� ����
	static string listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	// ������������� ������ ��������� � "������" �������� ����
	map <int, string> mainMenu;

	// ������ ����� - ������� ���� �������
	static string listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS];

	// ������������� ������ ��������� � "������" ���� �������
	map <int, string> alchemicalMenu;

	// ������ ����� - ������� ���� ����������
	static string listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	// ������������� ������ ��������� � "������" ���� ����������
	map <int, string> instructionsMenu;

	// ������ ����� - ������� ���� ������� ������������
	static string listOfBuyingIngredientsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];
	
	// ������������� ������ ��������� � "������" ���� ������� ������������
	map<int, string> buyingIngredientsMenu;

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	//// ���������� X ��� ����������
	//int instructionsXCoord;

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

#pragma endregion �������� ����������

	// ������� �������
	void chooseMenuItem(map <int, string> menu);

	// ������� ����� ������ ����
	void makeChoice();

	// �������� ������ � ������� ����
	void checkMainMenu();

	// �������� ������ � ���� ����������
	void checkInstructionsMenu();

	// �������� ����� ���� � ���� �������
	void checkAlchemicalMenu();

	// �������� ������ ������ � ���� ������� ������������
	void checkBuyingIngredientsMenu();

	// ���������� ��������
	void doAlchemy();

	// ������� ������������
	void buyIngredients();

	// ������� ������������ �� ���������� ������
	void buyIngredientsFromList();

	// ������� � ������� ��� ����� ������ ��������
	void eraseScreenAfterAlchemist();

	// ��������� ��� ����
	void fillAllMenu();

#pragma region ������ ������

	// �������� ��������� ���������
	void printTitle() override;

	// �������� "������" ������ ESC
	void printExitButton() override;

	// ������ �������� ���� � �����
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	// ������ ����������
	void printInstructions() override;

	// ������ ��������
	void printBye() override;

	// ������ ���� ��� ��������
	void printAlchemist();

	// ������ �������� ����
	void printMenuTitle(string title);

#pragma endregion ������ ������

};