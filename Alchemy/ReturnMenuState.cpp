#include "ReturnMenuState.h"
#include "AlchemicalUserInterface.h"

ReturnMenuState::ReturnMenuState(MenuState* previousMenuState, AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->previuosMenuState = previousMenuState;
    this->goToTitle = "Назад";
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