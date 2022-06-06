#include "UserInterface.h"

UserInterface::UserInterface()
{
	//this->alchemist = nullptr;

	this->titleXCoord = 0;
	this->menuCode = 0;
	this->currentXCursorCoord = 0;
	this->currentYCursorCoord = 0;

	this->keyBoard = this->keyBoard->getInstance();
}

void UserInterface::setTitle(string title)
{
	this->title = title;
}

void UserInterface::eraseScreenAfterTitle() const
{
	cout << goToXY(Y_COORD_AFTER_TITLE, 0);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void UserInterface::checkInput(int& value, int min, int max, string strChoice)
{
	cin >> value;

	// пока не попадает в диапазон
	while (value < min || max < value)
	{
		int numberOfSymbols = to_string(value).size();

		cout << goToXY(Y_COORD_AFTER_MENU_TITLE, strChoice.size() + 1 /*+ numberOfSymbols*/);

		string a = "\x1b[" + to_string(numberOfSymbols) + "P";
		//string a = "\x1b[" + to_string(numberOfSymbols) + "X";


		cout << a;

		//for (int i = 0; i < numberOfSymbols; ++i)
		//{
		//	cout << '\x1b[ <n> P';
		//}

		cin >> value;
	}
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

//void UserInterface::setXCoordInMiddle()
//{
//	titleXCoord = (calculateConsoleWidth() / 2) - (title.length() / 2);
//}

void UserInterface::printMenu(map <int, string> menu) const
{
	// Стартовый ключ в ассоциативном массиве
	int border = currentYCursorCoord + menu.size();

	// Печатаем ассоциативный массив
	for (int i = currentYCursorCoord; i < border; ++i)
	{
		if (i == currentYCursorCoord)
		{
			printTextWithBackground(menu[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// Печатаем пункт меню
			cout << menu[i] << endl;
	}
}

map<int, string> UserInterface::fillMenuMap(const int numberOfItems, const string listOfItems[])
{
	// Стартовый ключ в ассоциативном массиве
	int startKey = this->currentYCursorCoord;

	// Создаем ассоциативный массив
	map<int, string> menu;

	// Заполняем ассоциативный массив
	for (int i = 0; i < numberOfItems; ++i, ++startKey)
	{
		menu.emplace(startKey, listOfItems[i]);
	}

	return menu;
}

void UserInterface::checkMenuChoice() const
{
	// нажатая клавиша
	int key;

	do {

		this->keyBoard->waitForKey();

		key = this->keyBoard->getPressedKey();

	}	// Если нажатая клавиша не соответсвует кнопкам меню
	while (this->func(key));
}

void UserInterface::checkVerticalArrowsChoice(int borderYCoord, int keyCode, map <int, string> menu)
{
	// если граничная координата не равна текущей
	if (borderYCoord != this->currentYCursorCoord)
	{
		// Если кнопка вниз
		if (VK_DOWN == keyCode)
		{
			// Печатаем пункт меню без выделения
			cout << menu[currentYCursorCoord];

			// увеличиваем координаты
			++this->currentYCursorCoord;
		}
		// если кнопка вверх
		else
			// уменьшаем координаты
			--this->currentYCursorCoord;

		// Переходим по координатам
		cout << goToXY(this->currentYCursorCoord, 0);

		printMenu(menu);

		// Возвращаемся в координаты
		cout << goToXY(currentYCursorCoord, 0);
	}
}