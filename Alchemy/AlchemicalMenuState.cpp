#include "AlchemicalMenuState.h"
#include "MainMenuState.h"

AlchemicalMenuState::AlchemicalMenuState()
{
}

AlchemicalMenuState::AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Меню алхимии";
	this->goToTitle = "Алхимичить";
	this->numberOfStates = NUMBER_OF_ALCHEMICAL_MENU_ITEMS;
}

AlchemicalMenuState::~AlchemicalMenuState()
{
	clear();
}

void AlchemicalMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (AlchemicalMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	MenuState::printMenu();
}

void AlchemicalMenuState::setListOfStates()
{
	this->listOfStates.push_back(new CreatingPotionsMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new BuyingIngredientsMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new SellingIngredientsMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new EatingIngredientsMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new SellingPotionsMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new WorkWithTablesMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void AlchemicalMenuState::setListOfCreatingFunctions()
{
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createCreatingPotionsMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createBuyingIngredientsMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createSellingIngredientsMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createEatingIngredientsMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createSellingPotionsMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createWorkWithTablesMenuState);
	this->listOfCreatingFunctions.push_back(&AlchemicalMenuState::createReturnMenuState);
}

MenuState* AlchemicalMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void AlchemicalMenuState::fillStateCreatingFunctions()
{
	// Стартовый ключ в ассоциативном массиве
	int startKey = this->currentYCursorCoordState;

	// Заполняем ассоциативный массив
	for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
	{
		stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
	}
}

CreatingPotionsMenuState* AlchemicalMenuState::createCreatingPotionsMenuState()
{
	return new CreatingPotionsMenuState(this->alchemicalUserInterface);
}

BuyingIngredientsMenuState* AlchemicalMenuState::createBuyingIngredientsMenuState()
{
	return new BuyingIngredientsMenuState(this->alchemicalUserInterface);
}

SellingIngredientsMenuState* AlchemicalMenuState::createSellingIngredientsMenuState()
{
	return new SellingIngredientsMenuState(this->alchemicalUserInterface);
}

EatingIngredientsMenuState* AlchemicalMenuState::createEatingIngredientsMenuState()
{
	return new EatingIngredientsMenuState(this->alchemicalUserInterface);
}

SellingPotionsMenuState* AlchemicalMenuState::createSellingPotionsMenuState()
{
	return new SellingPotionsMenuState(this->alchemicalUserInterface);
}

WorkWithTablesMenuState* AlchemicalMenuState::createWorkWithTablesMenuState()
{
	return new WorkWithTablesMenuState(this->alchemicalUserInterface);
}

ReturnMenuState* AlchemicalMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

