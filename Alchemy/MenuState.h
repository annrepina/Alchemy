#pragma once
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Formatting.h"
#include "ServiceFunctions.h"
//#include "AlchemicalUserInterface.h"

using namespace std;



// Координаты
#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий

class AlchemicalUserInterface;

template <typename T>
class MenuState
{
public:
	
	// Конструктор по умолчанию
	MenuState();

	// Конструктор с параметром
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Конструктор копирования
	MenuState(MenuState const& copyMenuState);

	// Перегрузка оператора присваивания
	MenuState& operator = (MenuState const& right);

	// Деструктор
	virtual ~MenuState();

	// Задаем интерфейс
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать мееню
	virtual void printMenu();

	//void fillMenuStates();

protected:

	virtual MenuState* getNextState() = 0;

	// Задать список состояний
	virtual void setListOfStates() = 0;

	virtual void setListOfCreatingFunctions() = 0;

	// Экземпляр интерфейса
	AlchemicalUserInterface* alchemicalUserInterface;

	// Название меню
	string title;

	// Название меню при переходе в него
	string goToTitle;

	static int currentYCursorCoordState;

	static int currentXCursorCoordState;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

	// Флаг для выхода из главного цикла
	//bool exitFlag;

	// кол-во состояний
	int numberOfStates;

	// Печать название меню
	virtual void printMenuTitle();

	// Печать главного меню
	virtual void printMenuItems();

	// Принять решение
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// Ассоциативный массив состояний
	std::map<int, MenuState*> menuStates;

	//// Map функций, которые создают стейты
	//map<int, function<MenuState* ()> > stateCreatingFunctions;

	//vector< function<MenuState* (MenuState&)> > listOfCreatingFunctions;

	//std::map<int, string> str;

	// Список состояний этого меню
	vector<MenuState*> listOfStates;

	vector< function<MenuState* (T&)> > listOfCreatingFunctions;

	// Проверка выбора стрелочек вверх/вниз
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

	virtual void clear();

private:



};