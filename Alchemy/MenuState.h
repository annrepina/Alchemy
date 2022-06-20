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

template <typename T>
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

	//void fillMenuStates();

protected:

	virtual MenuState* getNextState() = 0;

	// ������ ������ ���������
	virtual void setListOfStates() = 0;

	virtual void setListOfCreatingFunctions() = 0;

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

	vector< function<MenuState* (T&)> > listOfCreatingFunctions;

	// �������� ������ ��������� �����/����
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

	virtual void clear();

private:



};