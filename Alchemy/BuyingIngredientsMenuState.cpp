#include "BuyingIngredientsMenuState.h"

BuyingIngredientsMenuState::BuyingIngredientsMenuState()
{
}

BuyingIngredientsMenuState::BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "���� ������� ������������";
    this->goToTitle = "������ �����������";
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
