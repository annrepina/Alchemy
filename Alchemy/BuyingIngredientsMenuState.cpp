#include "BuyingIngredientsMenuState.h"
#include "AlchemicalMenuState.h"

BuyingIngredientsMenuState::BuyingIngredientsMenuState()
{
}

BuyingIngredientsMenuState::BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "������� ������������";
    this->goToTitle = "������ �����������";
    this->numberOfStates = NUMBER_OF_BUYING_MENU_ITEMS;
}

void BuyingIngredientsMenuState::printMenu()
{
    // ���������� ���������� ������ ��� ������ � ����� ������
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (BuyingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

    MenuState::printMenu();
}

void BuyingIngredientsMenuState::setListOfStates()
{
    this->listOfStates.push_back(new BuyingIngredientsFromListMenuState(this->alchemicalUserInterface));
    this->listOfStates.push_back(new BuyNewIngredientsMenuState(this->alchemicalUserInterface));
    this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyingIngredientsMenuState::setListOfCreatingFunctions()
{
    // ���� ������ ������
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createBuyingIngredientsFromListMenuState);
        this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createBuyNewIngredientsMenuState);
        this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createReturnMenuState);
    }
}

BuyingIngredientsFromListMenuState* BuyingIngredientsMenuState::createBuyingIngredientsFromListMenuState()
{
    return new BuyingIngredientsFromListMenuState(this->alchemicalUserInterface);
}

BuyNewIngredientsMenuState* BuyingIngredientsMenuState::createBuyNewIngredientsMenuState()
{
    return new BuyNewIngredientsMenuState(this->alchemicalUserInterface);
}

ReturnMenuState* BuyingIngredientsMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

MenuState* BuyingIngredientsMenuState::getNextState()
{
    return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}