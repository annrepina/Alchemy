#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING		1	// минимально требуемое кол-во зелья для ПРОДАЖИ 

// Состояние меню - продажа зелий
class SellingPotionsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	SellingPotionsMenuState();

	// Конструктор с параметром
	SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (SellingPotionsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (SellingPotionsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	// Проверка введенного id на наличие этого id
	void checkPotionId(int& potionId);

	// Проверка введенного количества зелья на корректность
	void checkNumberOfPotion(int& numberOfPotion, int potionId);

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать меню
	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);

	// Печать ошибки и пользователь делает выбор снова
	void printErrorAndMakeChoiceAgain(int& potionId, int yCoord);

	// Печать ошибки и пользователь делает выбор снова
	void printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& potionId);

#pragma region МЕТОДЫ ПЕЧАТИ
};