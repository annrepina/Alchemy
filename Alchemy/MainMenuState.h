#pragma once
#include "MenuState.h"
#include "AlchemicalMenuState.h"
#include "InstructionsMenuState.h"

// Кол-ва
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// Кол-во пунктов в главном меню

class MainMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	MainMenuState();

	// Конструктор с параметрами
	MainMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~MainMenuState() override;

	// Печать меню
	void printMenu() override;

	AlchemicalMenuState* createAlchemicalMenuState();

	InstructionsMenuState* createInstructionsMenuState();

	// Map функций, которые создают стейты
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	void fillStateCreatingFunctions();

	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	MenuState* getNextState() override;

	//void clear() override;
	 
protected:



private:

	void setListOfStates() override;

	void setListOfCreatingFunctions() override; 
};


