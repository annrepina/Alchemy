#pragma once
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Formatting.h"
#include "ServiceFunctions.h"
//#include "AlchemicalUserInterface.h"

using namespace std;



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

	// ����������� �����������
	MenuState(MenuState const& copyMenuState);

	// ���������� ��������� ������������
	MenuState& operator = (MenuState const& right);

	// ����������
	virtual ~MenuState();

	// ������ ���������
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ �����
	virtual void printMenu();

	// ������ ������ ���������
	virtual void setListOfStates();

	virtual void setListOfCreatingFunctions();

	void fillMenuStates();

	virtual MenuState* getNextState();


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
	//bool exitFlag;

	// ���-�� ���������
	int numberOfStates;

	// ������ �������� ����
	virtual void printMenuTitle();

	// ������ �������� ����
	virtual void printMenuItems();

	// ������� �������
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// ������������� ������ ���������
	std::map<int, MenuState*> menuStates;

	//// Map �������, ������� ������� ������
	//map<int, function<MenuState* ()> > stateCreatingFunctions;

	//vector< function<MenuState* (MenuState&)> > listOfCreatingFunctions;

	//std::map<int, string> str;

	// ������ ��������� ����� ����
	vector<MenuState*> listOfStates;



	// �������� ������ ��������� �����/����
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

	virtual void clear();

private:

};