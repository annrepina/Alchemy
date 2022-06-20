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

	// Деструктор
	~MainMenuState() override;

	// Печать меню
	void printMenu() override;

private:

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - алхимическое меню
	AlchemicalMenuState* createAlchemicalMenuState();

	// Создать состояние - меню инструкций
	InstructionsMenuState* createInstructionsMenuState();

	// Заполнить map функций, которые создают стейты и их ключи
	void fillStateCreatingFunctions();

	// Получить следующее состояние
	MenuState* getNextState() override;

	// 
	void setListOfStates() override;

	void setListOfCreatingFunctions() override; 
};


