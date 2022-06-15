#pragma once
#include <string>

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

private:

	// Очистить память
	//void clear();
};

