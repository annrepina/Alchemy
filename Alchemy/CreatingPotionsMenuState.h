#pragma once
#include "MenuState.h"

class CreatingPotionsMenuState : public MenuState
{
public:

	CreatingPotionsMenuState();

	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~CreatingPotionsMenuState() override;

	// ������ ����
	void printMenu() override;

private:


};

