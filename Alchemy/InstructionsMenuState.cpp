#include "InstructionsMenuState.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "���������� � ��������� \"������������\"";
	this->goToTitle = "������ ���������� � ���������";
}

InstructionsMenuState::~InstructionsMenuState()
{
}

void InstructionsMenuState::setListOfStates()
{
}
