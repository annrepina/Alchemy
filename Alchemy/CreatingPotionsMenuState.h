#pragma once
#include "MenuState.h"

class CreatingPotionsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	CreatingPotionsMenuState();

	// Конструктор с параметрами
	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Деструктор
	~CreatingPotionsMenuState() override;

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
	map<int, function<MenuState* (CreatingPotionsMenuState&)> > stateCreatingFunctions;

	// Заполнить map функций, которые создают стейты и их ключи
	void fillStateCreatingFunctions();

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (CreatingPotionsMenuState&)> > listOfCreatingFunctions;

	//// Создать состояние - алхимическое меню
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// Создать состояние - меню инструкций
	//InstructionsMenuState* createInstructionsMenuState();
};

