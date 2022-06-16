#pragma once
#include <string>
#include <iostream>
#include "Formatting.h"
//#include "AlchemicalUserInterface.h"

using namespace std;

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

	// ������ �������� ����
	virtual void printMenuTitle();

private:

	// �������� ������
	//void clear();
};

