#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING		1	// минимально требуемое кол-во ингредиентов для ПРОДАЖИ 

// Состояние меню - продажа ингредиентов
class SellingIngredientsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	SellingIngredientsMenuState();

	// Конструктор с параметром
	SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (SellingIngredientsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (SellingIngredientsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	// Печать меню
	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);

	// Печать ошибки и пользователь делает выбор снова
	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	// Печать ошибки и пользователь делает выбор снова
	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	// Проверка введенного id на наличие этого id
	void checkIngredientsId(int& ingredientId);

	// Проверка введеного количества ингредиента на наличие такого кол-во
	void checkNumberOfIngredient(int& numberOfIngredient, int ingrdientId);
};