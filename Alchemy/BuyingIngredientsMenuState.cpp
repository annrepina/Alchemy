#include "BuyingIngredientsMenuState.h"
#include "AlchemicalMenuState.h"

BuyingIngredientsMenuState::BuyingIngredientsMenuState()
{
}

BuyingIngredientsMenuState::BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Покупка ингредиентов";
    this->goToTitle = "Купить ингредиенты";
    this->numberOfStates = NUMBER_OF_BUYING_MENU_ITEMS;
}

//BuyingIngredientsMenuState::~BuyingIngredientsMenuState()
//{
//    clear();
//}

void BuyingIngredientsMenuState::printMenu()
{
    // Сбрасываем координату каждый раз заходя в метод печати
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (BuyingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);


}

void BuyingIngredientsMenuState::setListOfStates()
{
    this->listOfStates.push_back(new BuyingIngredientsFromListMenuState(this->alchemicalUserInterface));
    this->listOfStates.push_back(new BuyNewIngredientsMenuState(this->alchemicalUserInterface));
    this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyingIngredientsMenuState::setListOfCreatingFunctions()
{
    this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createBuyingIngredientsFromListMenuState);
    this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createBuyNewIngredientsMenuState);
    this->listOfCreatingFunctions.push_back(&BuyingIngredientsMenuState::createReturnMenuState);
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
    return nullptr;
}

