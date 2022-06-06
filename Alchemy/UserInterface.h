#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "KeyBoard.h"

using namespace std;

using std::placeholders::_1;

// ����������
#define Y_COORD_AFTER_TITLE				4		// ���������� Y ����� ������� ���������
#define Y_COORD_AFTER_MENU_TITLE		9		// ���������� Y ����� ������ ��������� ����

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
	void setTitle(const string title);

protected:

	// �������� ���������
	string title;

	// ������� ��� ����������
	function<bool(int)> func;

	// ��������� ����������
	KeyBoard* keyBoard;

	// ��� ����
	int menuCode;

	// ��������� ������������� ������ ���� ��������
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[]);

	// �������� ������ � ����
	void checkMenuChoice() const;

	// �������� ������ ��������� �����/����
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode, map <int, string> menu);

	// ������� �� ������� ��, ����� �������� ���������
	void eraseScreenAfterTitle() const;

	// �������� �����
	void checkInput(int& value, int min, int max, string strChoice);

	//// ����������� ���������� � ��� ����������
	//void setXCoordInMiddle();

#pragma region ������ ������

	// �������� ��������� ���������
	virtual void printTitle() = 0;

	// �������� "������" ������ ESC
	virtual void printExitButton() = 0;

	// ������ �������� ����
	virtual void printMenu(map <int, string> menu) const;

	// ������ �������� ���� � �����
	virtual void printMenuInLoop(map<int, string> menu, string menuTitle) = 0;

	// ������ ����������
	virtual void printInstructions() = 0;

	// ������ ��������
	virtual void printBye() = 0;

#pragma endregion ������ ������

#pragma region ���������

	// �������� ��� ������ ������������ � ������� ����
	bool isMenuChoiceFalse(int key);

	// �� ���� �� ������ ������ �������?
	bool isArrowKeyFalse(int key);

#pragma endregion ���������

#pragma region ����������

	// ���������� � - ������ �������� ���������
	int titleXCoord;

	// ������� ���������� �
	int currentXCursorCoord;

	// ������� ���������� Y
	int currentYCursorCoord;

#pragma endregion ����������

private:

};

