#include "CreatingPotionsMenuState.h"

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "���� �������� �����";
    this->goToTitle = "������� �����";
    this->numberOfStates = 0;
}

//CreatingPotionsMenuState::~CreatingPotionsMenuState()
//{
//    clear();
//}

void CreatingPotionsMenuState::printMenu()
{
}

void CreatingPotionsMenuState::fillStateCreatingFunctions()
{
}

MenuState* CreatingPotionsMenuState::getNextState()
{
    return nullptr;
}

void CreatingPotionsMenuState::setListOfStates()
{
}

void CreatingPotionsMenuState::setListOfCreatingFunctions()
{
}
