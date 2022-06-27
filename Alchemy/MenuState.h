#pragma once
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Formatting.h"
#include "ServiceFunctions.h"

using namespace std;

// ����������
#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������
#define STANDARD_CURSOR_X_COORD			0		// ����������� ���������� X ������� 
#define Y_COORD_AFTER_MENU_TITLE_1		9		// ���������� Y ������ ����� ������ ��������� ����
#define Y_COORD_AFTER_MENU_TITLE_2		10		// ���������� Y ������ ����� ������ ��������� ����
#define Y_COORD_AFTER_MENU_TITLE_3		11		// ���������� Y ������ ����� ������ ��������� ����
#define Y_COORD_AFTER_MENU_TITLE_4		12		// ���������� Y ��������� ����� ������ ��������� ����

class AlchemicalUserInterface;

class MenuState
{
public:
	
	// ����������� �� ���������
	MenuState();

	// ����������� � ����������
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ����������� �����������
	MenuState(MenuState const& copyMenuState);

	// ���������� ��������� ������������
	MenuState& operator = (MenuState const& right);

	// ����������
	virtual ~MenuState();

	// ������ ���������
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	virtual void printMenu();

	//void fillMenuStates();

protected:

	// ��������� ����������
	AlchemicalUserInterface* alchemicalUserInterface;

	// �������� ����
	string title;

	// �������� ���� ��� �������� � ����
	string goToTitle;

	// ������� ���������� Y ������� 
	static int currentYCursorCoordState;

	// ������� ���������� X ������� 
	static int currentXCursorCoordState;

	// ��������� ���������� Y ��� ���������� ���������
	int boundaryYCoord;

	// ���-�� ��������� � ������� ���������
	int numberOfStates;

	// �������� ��������� ���������
	virtual MenuState* getNextState() = 0;

	// ������ ������ ���������
	virtual void setListOfStates() = 0;

	// ������ ������ ��������� ������ �������
	virtual void setListOfCreatingFunctions() = 0;

	// ������ �������� ����
	virtual void printMenuTitle();

	// ������ �������� ����
	virtual void printMenuItems();

	// ������� �������
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// ������������� ������ ���������
	std::map<int, MenuState*> menuStates;

	// ������ ��������� ����� ����
	vector<MenuState*> listOfStates;

	// �������� ������ ��������� �����/����
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

	// �������� ������
	virtual void clear();

private:

};