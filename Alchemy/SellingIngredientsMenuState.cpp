#include "SellingIngredientsMenuState.h"

SellingIngredientsMenuState::SellingIngredientsMenuState()
{
}

SellingIngredientsMenuState::SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Продажа ингредиентов";
	this->goToTitle = "Продать ингредиенты";
	this->numberOfStates = 0;
}

//SellingIngredientsMenuState::~SellingIngredientsMenuState()
//{
//	clear();
//}

void SellingIngredientsMenuState::printMenu()
{
}

MenuState* SellingIngredientsMenuState::getNextState()
{
	return nullptr;
}

void SellingIngredientsMenuState::setListOfStates()
{
}

void SellingIngredientsMenuState::setListOfCreatingFunctions()
{
}

