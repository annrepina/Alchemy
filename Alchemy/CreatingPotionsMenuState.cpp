#include "CreatingPotionsMenuState.h"

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Создание зелий";
    this->goToTitle = "Создать зелье";
    this->numberOfStates = 0;
}

//CreatingPotionsMenuState::~CreatingPotionsMenuState()
//{
//    clear();
//}

void CreatingPotionsMenuState::printMenu()
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
