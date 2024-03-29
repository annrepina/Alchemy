#include "UserInterface.h"

UserInterface::UserInterface()
{
	this->titleXCoord = 0;
	this->currentXCursorCoord = 0;
	this->currentYCursorCoord = 0;
	this->keyBoard = this->keyBoard->getInstance();
}

UserInterface::~UserInterface()
{
	this->keyBoard->release();
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

int UserInterface::checkInput(string value, int min, int max, string textOfRangeError, int yCoord, int xCoord)
{
	// �� ����� ������ ������� ������ �����
	bool success;

	int intValue;

	do
	{
		enter(value);

		if (value == "")
			continue;

		success = tryParseToInt(value);

		// ���� �� �����
		if (!success)
		{
			string textOfError = "�� ����� ������������ ��������, ���������� �����: ";

			printError(yCoord, xCoord, textOfError);

			continue;
		}

		// ��������� ������ � ���
		intValue = stoi(value);

		// ���� �� �������� � ��������
		if (intValue < min || max < intValue)
		{
			printError(yCoord, xCoord, textOfRangeError);
		}
		else
		{
			return intValue;
		}

	} while (true);
}

void UserInterface::enter(string& value)
{
	std::cin.ignore(0, EOF);
	getline(std::cin, value, '\n');
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

	printColoredText(textOfError, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

bool UserInterface::isArrowKeyFalse(int key)
{
	bool res = VK_UP != key && VK_DOWN != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

void UserInterface::printMenu(map <int, string> menu) const
{
	// ��������� ���� � ������������� �������
	int border = currentYCursorCoord + menu.size();

	// �������� ������������� ������
	for (int i = currentYCursorCoord; i < border; ++i)
	{
		if (i == currentYCursorCoord)
		{
			printTextWithBackground(menu[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// �������� ����� ����
			cout << menu[i] << endl;
	}
}

map<int, string> UserInterface::fillMenuMap(const int numberOfItems, const string listOfItems[])
{
	// ��������� ���� � ������������� �������
	int startKey = this->currentYCursorCoord;

	// ������� ������������� ������
	map<int, string> menu;

	// ��������� ������������� ������
	for (int i = 0; i < numberOfItems; ++i, ++startKey)
	{
		menu.emplace(startKey, listOfItems[i]);
	}

	return menu;
}

map<int, string> UserInterface::fillMenuMap(const int numberOfItems, const string listOfItems[], int yCoord)
{
	// ��������� ���� � ������������� �������
	int startKey = yCoord;

	// ������� ������������� ������
	map<int, string> menu;

	// ��������� ������������� ������
	for (int i = 0; i < numberOfItems; ++i, ++startKey)
	{
		menu.emplace(startKey, listOfItems[i]);
	}

	return menu;
}

void UserInterface::checkMenuChoice() const
{
	// ������� �������
	int key;

	do {

		this->keyBoard->waitForKey();

		key = this->keyBoard->getPressedKey();

	}	// ���� ������� ������� �� ������������ ������� ����
	while (this->func(key));
}

string UserInterface::checkInput(string& value, bool isString, int max, int min, int yCoord, int xCoord)
{
	int intRequest = 0;

	// ���� ��������� �����
	if (!isString)
	{
		intRequest = checkInput(value, 0, MAX_INT, "������ �������� �� ��������", yCoord, xCoord);
		value = to_string(intRequest);
	}
	else
	{
		do {
			enter(value);

			if (value == "")
				continue;

			else
				break;

		} while (true);
	}

	return value;
}

bool UserInterface::isEscKeyPressed()
{
	// ������� �������
	int key;

	this->keyBoard->waitForKey();

	key = this->keyBoard->getPressedKey();

	// ���� ������ esc
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