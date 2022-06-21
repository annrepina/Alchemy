#include "ReturnMenuState.h"
#include "AlchemicalUserInterface.h"

ReturnMenuState::ReturnMenuState(MenuState* previousMenuState, AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->previuosMenuState = previousMenuState;
    this->goToTitle = "Назад";
}

ReturnMenuState::~ReturnMenuState()
{
    clear();
}

void ReturnMenuState::printMenu()
{
    this->alchemicalUserInterface->setState(this->getNextState());
}

MenuState* ReturnMenuState::getNextState()
{
    return this->previuosMenuState;
}

void ReturnMenuState::setListOfStates()
{
}

void ReturnMenuState::setListOfCreatingFunctions()
{
}
