#include "MainMenuState.h"

MainMenuState::MainMenuState()
{

}

MainMenuState::MainMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Главное меню";
	this->numberOfStates = NUMBER_OF_MAIN_MENU_ITEMS;
}

MainMenuState::~MainMenuState()
{
	clear();
}

//void MainMenuState::printMenu()
//{
//
//}

void MainMenuState::printMenu()
{
	setListOfCreatingFunctions();

	fillMap<function<MenuState* (MainMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	MenuState::printMenu();
}

void MainMenuState::setListOfStates()
{
	this->listOfStates.push_back(new AlchemicalMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new InstructionsMenuState(this->alchemicalUserInterface));
}

void MainMenuState::setListOfCreatingFunctions()
{
	this->listOfCreatingFunctions.push_back(&MainMenuState::createAlchemicalMenuState);
	this->listOfCreatingFunctions.push_back(&MainMenuState::createInstructionsMenuState);	
}

AlchemicalMenuState* MainMenuState::createAlchemicalMenuState()
{
	return new AlchemicalMenuState(this->alchemicalUserInterface);
}

InstructionsMenuState* MainMenuState::createInstructionsMenuState()
{
	return new InstructionsMenuState(this->alchemicalUserInterface);
}

void MainMenuState::fillStateCreatingFunctions()
{
	// Стартовый ключ в ассоциативном массиве
	int startKey = this->currentYCursorCoordState;

	// Заполняем ассоциативный массив
	for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
	{
		stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
	}
}

MenuState* MainMenuState::getNextState()
{
	//this->stateCreatingFunctions[currentYCursorCoordState].operator();

	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

//void MainMenuState::clear()
//{
//	for (auto state : this->menuStates)
//	{
//		delete state.second;
//
//		state.second = nullptr;
//	}
//}
