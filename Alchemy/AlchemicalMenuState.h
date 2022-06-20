#pragma once
#include "MenuState.h"

#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	7		// ���-�� ������� � ������������ ����

class AlchemicalMenuState : public MenuState
{
public:

	AlchemicalMenuState();

	AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~AlchemicalMenuState() override;

protected:

private:

	void setListOfStates() override;

	void setListOfCreatingFunctions() override;

	MenuState* getNextState() override;
};

