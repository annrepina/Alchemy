#include "MainMenuState.h"

MainMenuState::MainMenuState()
{

}

MainMenuState::MainMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Так значит ты алхимик?";
	this->numberOfStates = NUMBER_OF_MAIN_MENU_ITEMS;
}

void MainMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

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
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&MainMenuState::createAlchemicalMenuState);
		this->listOfCreatingFunctions.push_back(&MainMenuState::createInstructionsMenuState);
	}
}

AlchemicalMenuState* MainMenuState::createAlchemicalMenuState()
{
	return new AlchemicalMenuState(this->alchemicalUserInterface);
}

InstructionsMenuState* MainMenuState::createInstructionsMenuState()
{
	return new InstructionsMenuState(this->alchemicalUserInterface);
}

MenuState* MainMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}
