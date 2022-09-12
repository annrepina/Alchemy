#pragma once
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "PotionTablePrinter.h"

#define MINIMUM_NUMBER_OF_POTIONTS								1	// Минимальное кол-во зелий

class AlchemicalMenuState;

// Сосотояние меню - работа с таблицей зелий
class WorkWithPotionTableMenuState : public WorkWithIngredientTableMenuState
{
public:

	// Конструктор по умолчанию
	WorkWithPotionTableMenuState();

	// Конструктор с параметром
	WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

protected:

	// Задать контент для печати
	void setContent() override;

	// Принтер таблицы зелий
	PotionTablePrinter* potionTablePrinter;

	// Задать список фильтров
	void setListOfColumnFilters() override;

	// Запустить меню фильтрации
	void launchFilterMenu() override;

	// Запустить меню сортировки
	void launchSortingMenu() override;

	// Искомая колонка является стринговой или интовой в тбалице?
	bool isStringColumn(int numberOfColumn) override;

	// Запустить сортировку
	void sortData() override;

	// Фильтровать данные
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