#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

// Состояние меню - поедание ингредиентов
class EatingIngredientsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	EatingIngredientsMenuState();

	// Конструктор с параметром
	EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (EatingIngredientsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (EatingIngredientsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	// Проверка id на наличие такого
	void checkIngredientsId(int& ingredientId);

	// Печать ошибки и пользователь делает выбор снова
	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	// Был ли неизвестен эффект у ингредиента
	bool wasUnknownEffect(int ingredientId);
};