#include "BuyNewIngredientsMenuState.h"

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState()
{
}

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "������� ���������� �������������";
    this->goToTitle = "������ ���������� �������������";
    this->numberOfStates = 0;
}

void BuyNewIngredientsMenuState::printMenu()
{
}

MenuState* BuyNewIngredientsMenuState::getNextState()
{
    return nullptr;
}

void BuyNewIngredientsMenuState::setListOfStates()
{
}

void BuyNewIngredientsMenuState::setListOfCreatingFunctions()
{
}
