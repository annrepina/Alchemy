#pragma once
#include "MenuState.h"

class InstructionsMenuState : public MenuState
{
public:

	InstructionsMenuState();

	InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~InstructionsMenuState();

	void setListOfStates() override;

protected:

private:

};

