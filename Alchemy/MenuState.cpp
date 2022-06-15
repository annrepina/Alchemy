#include "MenuState.h"

MenuState::MenuState()
{
	this->title = "";
}

MenuState::MenuState(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

MenuState::~MenuState()
{
}

void MenuState::setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

void MenuState::printMenu()
{

}
