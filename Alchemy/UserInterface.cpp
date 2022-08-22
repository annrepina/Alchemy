#include "UserInterface.h"

UserInterface::UserInterface()
{
	//this->alchemist = nullptr;

	this->titleXCoord = 0;
	this->menuCode = 0;
	this->currentXCursorCoord = 0;
	this->currentYCursorCoord = 0;

	this->keyBoard = this->keyBoard->getInstance();

	//this->state = new MainMenu(*this);
}

void UserInterface::setTitle(string title)
{
	this->title = title;
}

void UserInterface::setCurrentYCursorCoord(int yCoord)
{
	this->currentYCursorCoord = yCoord;
}

void UserInterface::setFunc(function<bool(int)> func)
{
	this->func = func;
}

void UserInterface::eraseScreenAfterTitle() const
{
	cout << goToXY(Y_COORD_AFTER_TITLE, 0);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

int UserInterface::checkInput(string value, int min, int max, string textOfRangeError, int yCoord)
{
	// не ввели всякие символы вместо числа
	bool succes; 

	int intValue;

	do
	{
		cin >> value;

		succes = tryParseToInt(value);

		if (!succes)
		{
			string textOfError = "Вы ввели недопустимое значение, попробуйте снова: ";

			printError(yCoord, 1, textOfError);

			continue;
		}

		// переводит строку в инт
		intValue = stoi(value);

		// если не попадаем в диапазон
		if (intValue < min || max < intValue)
		{
			printError(yCoord, 1, textOfRangeError);
		}
		else
		{
			break;
		}

	} while (true);

	return intValue;
}

int UserInterface::getCurrentYCursorCoord()
{
	return this->currentYCursorCoord;
}

int UserInterface::getCurrentXCursorCoord()
{
	return this->currentXCursorCoord;
}

function<bool(int)> UserInterface::getFunc()
{
	return this->func;
}

KeyBoard* UserInterface::getKeyBoard()
{
	return this->keyBoard;
}

void UserInterface::printError(int yCoord, int xCoord, string textOfError)
{
	cout << goToXY(yCoord, xCoord);

	cout << eraseSymbolsOnScreen(ONE_HUNDRED_SYMBOLS);

	printColoredText(textOfError, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
}

//bool UserInterface::isMenuChoiceFalse(int key)
//{
//	return key != VK_1 && key != VK_2 && key != VK_NUMPAD1 && key != VK_NUMPAD2 && key != VK_ESCAPE;
//}

bool UserInterface::isArrowKeyFalse(int key)
{
	bool res = VK_UP != key && VK_DOWN != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

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

map<int, string> UserInterface::fillMenuMap(const int numberOfItems, const string listOfItems[], int yCoord)
{
	// Стартовый ключ в ассоциативном массиве
	int startKey = yCoord;

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

bool UserInterface::isEscKeyPressed()
{
	// нажатая клавиша
	int key;

	this->keyBoard->waitForKey();

	key = this->keyBoard->getPressedKey();

	// если нажали esc
	if (key == VK_ESCAPE)
	{
		return true;
	}

	return false;
}

bool UserInterface::isEscKeyFalse(int key)
{
	bool res = VK_ESCAPE != key ;

	return res;
}

bool UserInterface::isEnterEscKeyFalse(int key)
{
	bool res = VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

