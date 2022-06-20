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

	// Map �������, ������� ������� ������
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	void fillStateCreatingFunctions();

	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	MenuState* getNextState() override;

private:




};

