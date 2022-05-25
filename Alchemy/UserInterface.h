#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "KeyBoard.h"
#include "Alchemist.h"
#include "IngredientBuilder.h"

using namespace std;

using std::placeholders::_1;

// ����������
#define TITLE_Y_COORD			1		// ���������� Y ������� ��� ������ �������� ���������
#define Y_COORD_AFTER_TITLE		4		// ���������� Y ����� ������� ���������
#define ACTION_MENU_Y_COORD		8		// ���������� Y ���� ��������
#define EXIT_Y_COORD			2		// ���������� Y ������ ������

// ���� ������
#define VK_1					0x31	// ������� 1
#define VK_2					0x32	// ������� 2
#define VK_NUMPAD1				0x61	// ������� �������� ���������� 1
#define VK_NUMPAD2				0x62	// ������� �������� ���������� 2
#define VK_ESCAPE				0x1B	// ������� ESC
#define VK_RETURN				0x0D	// ������� Enter
#define VK_LEFT					75		// ������� �� �������� �����
#define VK_UP					72		// ������� �� �������� �����
#define VK_RIGHT				77		// ������� �� �������� ������
#define VK_DOWN					80		// ������� �� �������� ����


#define NUMBER_OF_MAIN_MENU_ITEMS	6		// ���������� ������� ������� ���� � ���������� ������ � "��������"
#define TOTAL_NUMBER_OF_MENU_ITEMS	6		// ����� ���-�� ������� ���� � ����������

// ����� - ���������������� ���������
class UserInterface
{
public:

	// ����������� �� ���������
	UserInterface();

	//// ������ ����������
	//void print();

	// ���� ���������
	void mainloop();

	// ������ �������� ���������
	void setTitle(string title);

	// ������ ��� ��������
	void setAlchemist(Alchemist* alchemist);

private:

	// ������� (������������)
	Alchemist* alchemist;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// ������� ��� ����������
	function<bool(int)> func;

	// ������������� ������ ��������� � "������ ����"
	map <int, string> actionMenu;

	// ������ ����� - ������� ����
	static string listOfMenuItems[TOTAL_NUMBER_OF_MENU_ITEMS];

#pragma region ����������

	// ���������� � - ������ �������� ���������
	int titleXCoord;

	//int exitXCoord;

	// ������� ���������� �
	int currentXCursorCoord;

	// ������� ���������� Y
	int currentYCursorCoord;

#pragma endregion ����������

	// �������� ���������
	string title;

	//// ������� ������������� �������
	//int key;

	// ��������� ����������
	KeyBoard* keyBoard;

	// ����������� ���������� � ��� ����������
	void setXCoord();

	// ��������� ������������� ������ ���� ��������
	void fillActionMenuMap();

	//// ��������� ������� ������
	//void getKey();

	//// �������� ������ � ����
	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);

	// �������� ������ � ����
	void checkMenuChoice();

	// �������� ������ ��������� �����/����
	void checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode);

	//// ��������� ���� �� ������� �������� ���������
	//void checkExit();

	// ���������� ��������
	void doAlchemy();

#pragma region ������ ������

	// �������� ��������� ���������
	void printTitle();

	// ������ �������� ����
	void printMainMenu();

	// ������ ����������
	void printInstructions();

	//// ������ ���� � �������� � ����������� ����
	//void printContinueGameMenu();

	// �������� ���� ��������
	void printActionMenu();

	// �������� "������" ������ ESC
	void printExitButton();

#pragma endregion ������ ������

	// ������� �� ������� ��, ����� �������� ���������
	void eraseScreenAfterTitle();




#pragma region ���������

	// �������� ��� ������ ������������ � ������� ����
	bool isMenuChoiceFalse(int key);

	// �������� ��� ������ ����������� ��� �������� ����
	bool isContinueGameFalse(int key);

	// ���������� ������ ���������� ��� �����
	bool isContinue(int key);

	// �� ���� �� ������ ������ �������?
	bool isArrowKeyFalse(int key);

#pragma endregion ���������


};

