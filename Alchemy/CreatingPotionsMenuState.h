#pragma once
#include "MenuState.h"

class CreatingPotionsMenuState : public MenuState
{
public:

	CreatingPotionsMenuState();

	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~CreatingPotionsMenuState() override;

	// Печать меню
	void printMenu() override;

	// Map функций, которые создают стейты
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	void fillStateCreatingFunctions();

	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	MenuState* getNextState() override;

private:




};

