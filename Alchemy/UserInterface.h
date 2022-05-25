#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "KeyBoard.h"
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


// ����� - ���������������� ���������
class UserInterface
{
public:

	// ����������� �� ���������
	UserInterface();

	// ���� ���������
	virtual void launchMainLoop() = 0;

	// ������ �������� ���������
	void setTitle(string title);

protected:

	// ������� ��� ����������
	function<bool(int)> func;

	// ��������� ����������
	KeyBoard* keyBoard;

	// ������������� ������ ��������� � "������ ����"
	map <int, string> actionMenu;

	// ��������� ������������� ������ ���� ��������
	virtual void fillActionMenuMap() = 0;

	// �������� ������ � ����
	void checkMenuChoice();

	// �������� ������ ��������� �����/����
	void checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode);

	// ������� �� ������� ��, ����� �������� ���������
	void eraseScreenAfterTitle();

#pragma region ������ ������

	// �������� ��������� ���������
	virtual void printTitle() = 0;

	// �������� "������" ������ ESC
	virtual void printExitButton() = 0;

	// ������ �������� ����
	virtual void printMainMenu() = 0;

	// ������ ����������
	virtual void printInstructions() = 0;

#pragma endregion ������ ������

#pragma region ���������

	// �������� ��� ������ ������������ � ������� ����
	bool isMenuChoiceFalse(int key);

#pragma endregion ���������

private:

#pragma region ����������

	// ���������� � - ������ �������� ���������
	int titleXCoord;

	// ������� ���������� �
	int currentXCursorCoord;

	// ������� ���������� Y
	int currentYCursorCoord;

#pragma endregion ����������

	// �������� ���������
	string title;

	// ����������� ���������� � ��� ����������
	void setXCoord();


	//// �������� ������ � ����
	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);






#pragma region ������ ������

	//// ������ �������� ����
	//void printMainMenu();



	//// ������ ���� � �������� � ����������� ����
	//void printContinueGameMenu();

	// �������� ���� ��������
	void printActionMenu();

#pragma endregion ������ ������






#pragma region ���������



	// �������� ��� ������ ����������� ��� �������� ����
	bool isContinueGameFalse(int key);

	// ���������� ������ ���������� ��� �����
	bool isContinue(int key);

	// �� ���� �� ������ ������ �������?
	bool isArrowKeyFalse(int key);

#pragma endregion ���������


};

