#include "WorkWithPotionTableMenuState.h"
#include "AlchemicalMenuState.h"

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState()
{
}

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "������ � �������";
    this->goToTitle = "�������� � �������";
    this->numberOfStates = 1;
}

void WorkWithPotionTableMenuState::printMenu()
{
}

MenuState* WorkWithPotionTableMenuState::getNextState()
{
    return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void WorkWithPotionTableMenuState::setListOfStates()
{
    this->listOfCreatingFunctions.push_back(&WorkWithPotionTableMenuState::createReturnMenuState);
}

void WorkWithPotionTableMenuState::setListOfCreatingFunctions()
{
    // ���� ������ ������
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&WorkWithPotionTableMenuState::createReturnMenuState);
    }
}

ReturnMenuState* WorkWithPotionTableMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
