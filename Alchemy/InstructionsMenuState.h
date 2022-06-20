#pragma once
#include "MenuState.h"

class InstructionsMenuState : public MenuState
{
public:

	InstructionsMenuState();

	InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~InstructionsMenuState() override;

	void setListOfStates() override;

protected:

private:

};

