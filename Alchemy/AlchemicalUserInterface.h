#pragma once
#include "UserInterface.h"

class AlchemicalUserInterface : public UserInterface
{
public:

	// ����������� �� ���������
	AlchemicalUserInterface();

private:

};



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

