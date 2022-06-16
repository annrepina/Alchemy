#pragma once
#include <string>
#include <iostream>
#include "Formatting.h"
//#include "AlchemicalUserInterface.h"

using namespace std;

class AlchemicalUserInterface;

class MenuState
{
public:
	
	// Конструктор по умолчанию
	MenuState();

	// Конструктор с параметром
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Деструктор
	virtual ~MenuState();

	// Задаем интерфейс
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать мееню
	virtual void printMenu();

protected:

	// Экземпляр интерфейса
	AlchemicalUserInterface* alchemicalUserInterface;

	// Название меню
	string title;

	// Печать название меню
	virtual void printMenuTitle();

private:

	// Очистить память
	//void clear();
};

