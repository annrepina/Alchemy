#pragma once
//#include <string>
//#include <iostream>
//#include <map>
//#include <functional>
//#include "Formatting.h"
//#include "ServiceFunctions.h"
//
//using namespace std;
//
//// Координаты
//#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий
//
//class AlchemicalUserInterface;
//
//template<typename T>
//class MenuStateTemp
//{
//public:
//
//	// Конструктор по умолчанию
//	MenuStateTemp()
//	{
//		this->title = "";
//		this->goToTitle = "";
//		this->alchemicalUserInterface = nullptr;
//		this->boundaryYCoord = MAIN_MENU_Y_COORD;
//		//this->exitFlag = false;
//		this->numberOfStates = 0;
//	}
//
//	// Конструктор с параметром
//	MenuStateTemp(AlchemicalUserInterface* alchemicalUserInterface)
//	{
//		this->alchemicalUserInterface = alchemicalUserInterface;
//	}
//
//	// Конструктор копирования
//	MenuStateTemp(MenuStateTemp const& copyMenuState)
//	{
//		this->alchemicalUserInterface = copyMenuState.alchemicalUserInterface;
//		this->boundaryYCoord = copyMenuState.boundaryYCoord;
//		this->goToTitle = copyMenuState.goToTitle;
//		this->numberOfStates = copyMenuState.numberOfStates;
//		this->title = copyMenuState.title;
//	}
//
//	// Перегрузка оператора присваивания
//	MenuStateTemp& operator = (MenuStateTemp const& right)
//	{
//		if (right.alchemicalUserInterface != nullptr)
//		{
//			this->alchemicalUserInterface = right.alchemicalUserInterface;
//			this->boundaryYCoord = right.boundaryYCoord;
//			this->goToTitle = right.goToTitle;
//			this->numberOfStates = right.numberOfStates;
//			this->title = right.title;
//		}
//		// TODO: вставьте здесь оператор return
//
//		return *this;
//	}
//
//	// Деструктор
//	virtual ~MenuStateTemp()
//	{
//		clear();
//	}
//
//	// Задаем интерфейс
//	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
//	{
//		this->alchemicalUserInterface = alchemicalUserInterface;
//	}
//
//	// Печать меню
//	virtual void printMenu()
//	{
//		// Сбрасываем координату каждый раз заходя в метод печати
//		currentYCursorCoordState = MAIN_MENU_Y_COORD;
//
//		this->setListOfStates();
//
//		fillMap<MenuState*>(menuStates, listOfStates, this->currentYCursorCoordState, this->numberOfStates);
//
//		printMenuTitle();
//
//		printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
//		cout << endl;
//
//		printMenuItems();
//
//		cout << goToXY(/*this->alchemicalUserInterface->getCurrentYCursorCoord()*/this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);
//
//		chooseMenuItem();
//
//		this->alchemicalUserInterface->setState(this->getNextState());
//	}
//
//	//void fillMenuStates();
//
//protected:
//
//	// Экземпляр интерфейса
//	AlchemicalUserInterface* alchemicalUserInterface;
//
//	// Название меню
//	string title;
//
//	// Название меню при переходе в него
//	string goToTitle;
//
//	// текущая координата Y курсора 
//	static int currentYCursorCoordState = MAIN_MENU_Y_COORD;
//
//	// текущая координата X курсора 
//	static int currentXCursorCoordState = 0;
//
//	// Граничная координата Y для управления стрелками
//	int boundaryYCoord;
//
//	// кол-во состояний у данного состояния
//	int numberOfStates;
//
//	// Получить следующее состояние
//	virtual MenuStateTemp* getNextState() = 0;
//
//	// Задать список состояний
//	virtual void setListOfStates() = 0;
//
//	// Задать список создающих стейты функций
//	virtual void setListOfCreatingFunctions() = 0;
//
//	// Печать название меню
//	virtual void printMenuTitle()
//	{
//		this->currentXCursorCoordState = calculateXCoordInMiddle(title);
//
//		//this->alchemicalUserInterface->currentXCursorCoord = calculateXCoordInMiddle(title);
//
//		//this->currentXCursorCoord = calculateXCoordInMiddle(title);
//
//		/*cout << goToXY(this->alchemicalUserInterface->getCurrentYCursorCoord() - TWO_LINES, this->alchemicalUserInterface->getCurrentXCursorCoord());*/
//
//		cout << goToXY(this->currentYCursorCoordState - TWO_LINES, this->currentXCursorCoordState);
//
//		printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
//
//		cout << endl;
//	}
//
//	// Печать главного меню
//	virtual void printMenuItems()
//	{
//
//		int border = this->boundaryYCoord + this->menuStates.size();
//
//		// Печатаем ассоциативный массив
//		for (int i = this->currentYCursorCoordState; i < border; ++i)
//		{
//			if (i == this->currentYCursorCoordState)
//			{
//				printTextWithBackground(this->menuStates[i]->goToTitle, R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
//				cout << endl;
//			}
//
//			else
//				// Печатаем пункт меню
//				cout << menuStates[i]->goToTitle << endl;
//		}
//	}
//
//	// Принять решение
//	virtual void chooseMenuItem()
//	{
//		this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));
//
//		// Флаг для выхода из цикла, но не выход из программы
//		bool innerExitFlag = false;
//
//		do
//		{
//			// Проверяем нажатую кнопку
//			this->alchemicalUserInterface->checkMenuChoice();
//
//			//checkMenuChoice();
//
//			//switch (this->keyBoard->getPressedKey())
//			switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
//			{
//			case VK_UP:
//			{
//				// Проверяем стрелочки
//				/*this->alchemicalUserInterface->checkVerticalArrowsChoice(this->alchemicalUserInterface->getBoundaryYCoord(), VK_UP, menu);*/
//				this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);
//
//				//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
//			}
//			break;
//
//			case VK_DOWN:
//			{
//				// Проверяем стрелочки
//				this->checkVerticalArrowsChoice(this->boundaryYCoord + menuStates.size() - 1, VK_DOWN);
//
//				//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
//			}
//			break;
//
//			case VK_RETURN:
//			{
//				// Сделать выбор пункта меню
//				//makeChoice(innerExitFlag);// !! Осуществление действий
//
//				// выход из цикла
//				innerExitFlag = true;
//			}
//			break;
//
//			case VK_ESCAPE:
//			{
//				this->alchemicalUserInterface->setExitFlag(true);
//				//exitFlag = true;
//			}
//			break;
//			}
//		} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
//	}
//
//	// Ассоциативный массив состояний
//	std::map<int, MenuStateTemp*> menuStates;
//
//	// Список состояний этого меню
//	vector<MenuStateTemp*> listOfStates;
//
//	// Проверка выбора стрелочек вверх/вниз
//	void checkVerticalArrowsChoice(int borderYCoord, int keyCode)
//	{
//		// если граничная координата не равна текущей
//		if (borderYCoord != this->currentYCursorCoordState)
//		{
//			// Если кнопка вниз
//			if (VK_DOWN == keyCode)
//			{
//				// Печатаем пункт меню без выделения
//				cout << menuStates[currentYCursorCoordState]->goToTitle;
//
//				// увеличиваем координаты
//				++this->currentYCursorCoordState;
//			}
//			// если кнопка вверх
//			else
//				// уменьшаем координаты
//				--this->currentYCursorCoordState;
//
//			// Переходим по координатам
//			cout << goToXY(this->currentYCursorCoordState, 0);
//
//			printMenuItems();
//
//			// Возвращаемся в координаты
//			cout << goToXY(currentYCursorCoordState, 0);
//		}
//	}
//
//	// Очистить память
//	virtual void clear()
//	{
//		for (auto state : this->listOfStates)
//		{
//			delete state;
//
//			state = nullptr;
//		}
//	}
//
//	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
//	map<int, function<MenuStateTemp* (T&)> > stateCreatingFunctions;
//
//	// Заполнить map функций, которые создают стейты и их ключи
//	void fillStateCreatingFunctions()
//	{
//		// Стартовый ключ в ассоциативном массиве
//		int startKey = this->currentYCursorCoordState;
//
//		// Заполняем ассоциативный массив
//		for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
//		{
//			stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
//		}
//	}
//
//	// Вектор функций, которые создают стейты
//	vector< function<MenuStateTemp* (T&)> > listOfCreatingFunctions;
//
//private:
//
//};


