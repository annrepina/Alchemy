#include "BuyingIngredientsFromListMenuState.h"
#include "BuyingIngredientsMenuState.h"

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState()
{
}

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Покупка ингредиентов из \"Котелка Аркадии\"";
	this->goToTitle = "Купить ингредиенты из \"Котелка Аркадии\"";
	this->numberOfStates = 1;
}

//BuyingIngredientsFromListMenuState::~BuyingIngredientsFromListMenuState()
//{
//}

void BuyingIngredientsFromListMenuState::printMenu()
{
}

MenuState* BuyingIngredientsFromListMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void BuyingIngredientsFromListMenuState::setListOfStates()
{



	this->listOfStates.push_back(new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyingIngredientsFromListMenuState::setListOfCreatingFunctions()
{




	this->listOfCreatingFunctions.push_back(&BuyingIngredientsFromListMenuState::createReturnMenuState);
}

ReturnMenuState* BuyingIngredientsFromListMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

