#pragma once
#include "MenuState.h"

class AlchemicalMenuState : public MenuState
{
public:

	AlchemicalMenuState();

	AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~AlchemicalMenuState() override;

	void setListOfStates() override;

	//void clear() override;

protected:

private:


};

