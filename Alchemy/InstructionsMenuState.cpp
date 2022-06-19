#include "InstructionsMenuState.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Инструкции к программе \"Зельеварение\"";
	this->goToTitle = "Читать инструкцию к программе";
}

InstructionsMenuState::~InstructionsMenuState()
{
}

void InstructionsMenuState::setListOfStates()
{
}
