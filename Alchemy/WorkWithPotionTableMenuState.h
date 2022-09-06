#pragma once
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "PotionTablePrinter.h"

#define MINIMUM_NUMBER_OF_POTIONTS								1	// Минимальное кол-во зелий

class AlchemicalMenuState;

class WorkWithPotionTableMenuState : public WorkWithIngredientTableMenuState
{
public:

	WorkWithPotionTableMenuState();

	WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

	// Печать меню
	void printMenu() override;

protected:

	void setContent() override;

	PotionTablePrinter* potionTablePrinter;

	//virtual void sortData();

	void setListOfColumnTitles() override;

	void launchFilterMenu() override;

	void launchSortingMenu() override;

	// Искомая колонка является стринговой или интовой в тбалице?
	bool isStringColumn(int numberOfColumn) override;

	// Запустить сортировку
	void sortData() override;

	void filterData() override;

private:

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithPotionTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithPotionTableMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();
};

