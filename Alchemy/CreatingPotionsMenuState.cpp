#include "CreatingPotionsMenuState.h"

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Меню создания зелий";
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
