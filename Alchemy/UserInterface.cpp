#include "UserInterface.h"

UserInterface::UserInterface()
{
	//this->alchemist = nullptr;

	this->titleXCoord = 0;
	this->currentXCursorCoord = 0;
	this->currentYCursorCoord = 0;

	this->keyBoard = this->keyBoard->getInstance();
}

void UserInterface::setTitle(string title)
{
	this->title = title;
}

void UserInterface::eraseScreenAfterTitle()
{
	cout << goToXY(Y_COORD_AFTER_TITLE, 0);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

bool UserInterface::isMenuChoiceFalse(int key)
{
	return key != VK_1 && key != VK_2 && key != VK_NUMPAD1 && key != VK_NUMPAD2 && key != VK_ESCAPE;
}

//bool UserInterface::isContinue(int key)
//{
//	return VK_RETURN != key && VK_ESCAPE != key;
//}

bool UserInterface::isArrowKeyFalse(int key)
{
	bool res = VK_UP != key && VK_DOWN != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

void UserInterface::setXCoord()
{
	titleXCoord = (calculateConsoleWidth() / 2) - (title.length() / 2);
}

void UserInterface::fillActionMenuMap(const int menuYCoord, const int numberOfItems, const string listOfItems[], map<int, string> menu)
{
	// Стартовый ключ в ассоциативном массиве
	int startKey = menuYCoord;

	// Заполняем ассоциативный массив
	for (int i = 0; i < numberOfItems; ++i, ++startKey)
	{
		menu.emplace(startKey, listOfItems[i]);
	}
}

void UserInterface::checkMenuChoice()
{
	// нажатая клавиша
	int key;

	do {

		this->keyBoard->waitForKey();

		key = this->keyBoard->getPressedKey();

	}	// Если нажатая клавиша не соответсвует кнопкам меню
	while (this->func(key));
}

void UserInterface::checkArrowsChoice(bool &exitFlag, int BorderYCoord, int keyCode, map <int, string> actionMenu)
{
	// Сбрасываем флаг
	exitFlag = false;

	// если граничная координата не равна текущей
	if (BorderYCoord != this->currentYCursorCoord)
	{
		// Если кнопка вниз
		if (VK_DOWN == keyCode)
		{
			// Печатаем пункт меню без выделения
			cout << actionMenu[currentYCursorCoord] << endl;

			// увеличиваем координаты
			++this->currentYCursorCoord;
		}
		// если кнопка вверх
		else
			// уменьшаем координаты
			--this->currentYCursorCoord;

		// Переходим по координатам
		cout << goToXY(this->currentYCursorCoord, 1);

		// печатаем главное меню действий
		for (int i = currentYCursorCoord; i < MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS; ++i)
		{
			if (i == currentYCursorCoord)
			{
				printTextWithBackground(actionMenu[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			}

			else
				// Печатаем пункт меню
				cout << actionMenu[i] << endl;
		}

		// Возвращаемся в координаты
		cout << goToXY(currentYCursorCoord, 1);
	}
}