#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING		1	// минимально требуемое кол-во ингредиентов для ПРОДАЖИ 

class SellingIngredientsMenuState : public MenuState
{
public:

	SellingIngredientsMenuState();

	SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingIngredientsMenuState() override;

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

	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);

	//// Печать выбора id и возвращене резульата
	//int printChoiceId(int yCoord, int xCoord);

	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);


	// Проверка введенного id на наличие этого id
	void checkIngredientsId(int& ingredientId);

	void checkNumberOfIngredient(int& numberOfIngredient, int ingrdientId);

	//void decreaseNumberOfIngredients(int igredientId);

};

