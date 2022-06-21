#include "BuyingIngredientsMenuState.h"

BuyingIngredientsMenuState::BuyingIngredientsMenuState()
{
}

BuyingIngredientsMenuState::BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Меню покупки ингредиентов";
    this->goToTitle = "Купить ингредиенты";
    this->numberOfStates = 0;
}

//BuyingIngredientsMenuState::~BuyingIngredientsMenuState()
//{
//    clear();
//}

void BuyingIngredientsMenuState::printMenu()
{
}

void BuyingIngredientsMenuState::setListOfStates()
{
}

void BuyingIngredientsMenuState::setListOfCreatingFunctions()
{
}

MenuState* BuyingIngredientsMenuState::getNextState()
{
    return nullptr;
}

void BuyingIngredientsMenuState::fillStateCreatingFunctions()
{
}
