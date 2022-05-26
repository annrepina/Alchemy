#pragma once
#include "UserInterface.h"
#include "Alchemist.h"
#include "IngredientBuilder.h"

//// ����������
//#define MENU_Y_COORD					9		// ���������� Y ���� ��������

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

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	// ������� �������
	void chooseMenuItem(map <int, string> menu);

	// ���������� ��������
	void doAlchemy();

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

	// ������ ���� ��� ��������
	void printAlchemist();

#pragma endregion ������ ������

};