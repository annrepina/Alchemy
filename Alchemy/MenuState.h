#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Formatting.h"
//#include "AlchemicalUserInterface.h"

using namespace std;

// ���-��
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// ���-�� ������� � ������� ����

// ����������
#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������

class AlchemicalUserInterface;

class MenuState
{
public:
	
	// ����������� �� ���������
	MenuState();

	// ����������� � ����������
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ����������
	virtual ~MenuState();

	// ������ ���������
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ �����
	virtual void printMenu();

protected:

	// ��������� ����������
	AlchemicalUserInterface* alchemicalUserInterface;

	// �������� ����
	string title;

	// �������� ���� ��� �������� � ����
	string goToTitle;

	static int currentYCursorCoordState;

	static int currentXCursorCoordState;

	// ��������� ���������� Y ��� ���������� ���������
	int boundaryYCoord;

	// ���� ��� ������ �� �������� �����
	bool exitFlag;

	// ������ �������� ����
	virtual void printMenuTitle();

	// ������ �������� ����
	virtual void printMenuItems();

	// ������� �������
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// ������������� ������ ���������
	std::map<int, MenuState*> menuStates;

	std::map<int, string> str;

	// ������ ��������� ����� ����
	MenuState* listOfStates[NUMBER_OF_MAIN_MENU_ITEMS];

	// ������ ������ ���������
	virtual void setListOfStates() = 0;

	// �������� ������ ��������� �����/����
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

private:

};