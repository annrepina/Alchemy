#include "WorkWithTablesMenuState.h"

WorkWithTablesMenuState::WorkWithTablesMenuState()
{
}

WorkWithTablesMenuState::WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������ � ����������";
	this->goToTitle = "�������� � ����������";
	this->numberOfStates = WORK_WITH_TABLES_MENU_ITEMS;
}

//WorkWithTablesMenuState::~WorkWithTablesMenuState()
//{
//	clear();
//}

void WorkWithTablesMenuState::printMenu()
{
}

MenuState* WorkWithTablesMenuState::getNextState()
{
	return nullptr;
}

void WorkWithTablesMenuState::setListOfStates()
{
}

void WorkWithTablesMenuState::setListOfCreatingFunctions()
{
}

