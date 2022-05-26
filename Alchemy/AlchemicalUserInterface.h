#pragma once
#include "UserInterface.h"
#include "Alchemist.h"
#include "IngredientBuilder.h"

// ����������
#define TITLE_Y_COORD					1		// ���������� Y ������� ��� ������ �������� ���������
#define EXIT_Y_COORD					2		// ���������� Y ������ ������
#define Y_COORD_AFTER_ALCHEMIST			8		// ���������� Y ����� ������ ��������
#define MAIN_MENU_Y_COORD				9		// ���������� Y ���� ��������
#define INSTRUCTIONS_Y_COORD			10
#define STANDARD_CURSOR_X_COORD			0		// ����������� ���������� X ������� 


// ���-��
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// ���-�� ������� � ������� ����
#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	5		// ���-�� ������� � ������������ ����

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
		InstructionsMenu
	};

	// ���� ������� � ������� ����
	enum MainMenuCode
	{
		DoAlchemy = MAIN_MENU_Y_COORD,
		ReadInstructions
	};

	enum InstructionsMenuCode
	{
		Return = INSTRUCTIONS_Y_COORD,
		Exit
	};

	// ������� (������������)
	Alchemist* alchemist;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

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

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	// ���������� X ��� ����������
	int instructionsXCoord;

	// ��������� ���������� Y ��� ���������� ���������
	int boundaryYCoord;

	// �������� ����������
	string instructionsTitle;

	// ������� �������
	void chooseMenuItem(map <int, string> menu);

	// ������� ����� ������ ����
	void makeChoice();

	// �������� ������ � ������� ����
	void checkChoiceInMainMenu();

	// �������� ������ � ���� ����������
	void checkChoiceInInstructionsMenu();

	// ���������� ��������
	void doAlchemy();

	// ������� � ������� ��� ����� ������ ��������
	void eraseScreenAfterAlchemist();

#pragma region ������ ������

	// �������� ��������� ���������
	void printTitle() override;

	// �������� "������" ������ ESC
	void printExitButton() override;

	// ������ �������� ���� � �����
	void printMenuInLoop(map <int, string> menu) override;

	// ������ ����������
	void printInstructions() override;

	// �������� ���� ��������
	void printActionMenu() override;

	// ������ ��������
	void printBye() override;

	// ������ ���� ��� ��������
	void printAlchemist();

#pragma endregion ������ ������

};