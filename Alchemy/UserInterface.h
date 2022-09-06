#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "ServiceFunctions.h"
#include "KeyBoard.h"
//#include "MenuState.h"
//#include "MenuState.h"

using namespace std;

using std::placeholders::_1;

#define MAX_INT							2147483647	// ����� ������� ����� int 

// ����������
#define Y_COORD_AFTER_TITLE				4		// ���������� Y ����� ������� ���������
#define Y_COORD_AFTER_MENU_TITLE_1		9		// ���������� Y ����� ������ ��������� ����

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

#define EXIT_INT					-1		// �������� int � ������ ������


// ����� - ���������������� ���������
class UserInterface
{
public:

	// ����������� �� ���������
	UserInterface();

	// ���� ���������
	virtual void launchMainLoop() = 0;

	// ������� ��� ����������
	function<bool(int)> func;

#pragma region �������

	// ������ �������� ���������
	void setTitle(const string title);

	// ������ ��� ������� ���������� Y
	void setCurrentYCursorCoord(int yCoord);

	// ������ ��� �������
	void setFunc(function<bool(int)> func);

#pragma endregion �������

#pragma region �������

	// ������ ��� ��������� ������� ���������� Y
	int getCurrentYCursorCoord();

	// ������ ��� ��������� ������� ���������� X
	int getCurrentXCursorCoord();

	// �������� �������
	function<bool(int)> getFunc();

	// �������� �����
	KeyBoard* getKeyBoard();

#pragma endregion �������

#pragma region ���������

	// �� ���� �� ������ ������ �������?
	bool isArrowKeyFalse(int key);

	// ���� �� ������ ������� ������?
	virtual bool isEscKeyPressed();

	// ���� �� ������ ������� ������?
	virtual bool isEscKeyFalse(int key);

	// �� ���� ������ Enter � Esc
	bool isEnterEscKeyFalse(int key);

#pragma endregion ���������

	// �������� ������ � ����
	void checkMenuChoice() const;

	// �������� �����
	virtual string checkInput(string& value, bool isString, int max, int min, int yCoord, int xCoord);

	// ������ ������ ��-�� ������������� �����
	virtual void printError(int yCoord, int xCoord, string textOfError);

protected:

	// �������� ���������
	string title;

	// ��������� ����������
	KeyBoard* keyBoard;

	//// ��� ����
	//int menuCode;

	// ��������� ������������� ������ ���� ��������
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[]);

	// ����������� ������� ���������� �������������� �������� � ������������
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[], int yCoord);

	// ������� �� ������� ��, ����� �������� ���������
	void eraseScreenAfterTitle() const;

	// �������� �����
	int checkInput(string value, int min, int max, string textOfRangeError, int yCoord, int xCoord);

#pragma region ������ ������

	// �������� ��������� ���������
	virtual void printTitle() = 0;

	// �������� "������" ������ ESC
	virtual void printExitButton() = 0;

	// ������ �������� ����
	virtual void printMenu(map <int, string> menu) const;

	// ������ �������� ���� � �����
	virtual void printMenuInLoop(map<int, string> menu, string menuTitle) = 0;

	// ������ ��������
	virtual void printBye() = 0;

#pragma endregion ������ ������

	// ���������� � - ������ �������� ���������
	int titleXCoord;

	// ������� ���������� �
	int currentXCursorCoord;

	// ������� ���������� Y
	int currentYCursorCoord;

private:

};

