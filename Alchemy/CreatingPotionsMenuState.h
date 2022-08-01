#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"
#include "PotionBuilder.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING		2	// минимально требуемое кол-во ингредиентов для смешивания 


class CreatingPotionsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	CreatingPotionsMenuState();

	// Конструктор с параметрами
	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

private:

	// строитель зелья
	PotionBuilder* potionBuilder;

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (CreatingPotionsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (CreatingPotionsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void printMenu(string choiceFirstIngredient, string choiceSecondIngredient);

	// Печать выбора id
	int printChoiceId(int yCoord, int xCoord);

	// уменьшить кол-во ингредиентов
	void decreaseNumberOfIngredients(int firstIngredientId, int secondIngredientId);

	// Проверка введенных id на совпадение
	void checkIngredientsId(int &firstIngredientId, int &secondIngredientId);

	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId);

	void printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord);

	void checkIdForEquality(int& firstIngredientId, int secondIngredientId, int YCoord);

	//// Действия для выхода из меню
	//void exitMenu();

};

