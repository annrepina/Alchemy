#include "EatingIngredientsMenuState.h"

EatingIngredientsMenuState::EatingIngredientsMenuState()
{
}

EatingIngredientsMenuState::EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Меню поедания ингредиентов";
	this->goToTitle = "Съесть ингредиент";
	this->numberOfStates = 0;
}

EatingIngredientsMenuState::~EatingIngredientsMenuState()
{
	clear();
}

void EatingIngredientsMenuState::printMenu()
{
}

MenuState* EatingIngredientsMenuState::getNextState()
{
	return nullptr;
}

void EatingIngredientsMenuState::setListOfStates()
{
}

void EatingIngredientsMenuState::setListOfCreatingFunctions()
{
}

void EatingIngredientsMenuState::fillStateCreatingFunctions()
{
}
