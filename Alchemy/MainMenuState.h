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

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override; 

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	// Заполнить map функций, которые создают стейты и их ключи
	void fillStateCreatingFunctions();

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - алхимическое меню
	AlchemicalMenuState* createAlchemicalMenuState();

	// Создать состояние - меню инструкций
	InstructionsMenuState* createInstructionsMenuState();
};


