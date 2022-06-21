#include "WorkWithTablesMenuState.h"

WorkWithTablesMenuState::WorkWithTablesMenuState()
{
}

WorkWithTablesMenuState::WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Работа с инвентарем";
	this->goToTitle = "Работать с инвентарем";
	this->numberOfStates = 0;
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

