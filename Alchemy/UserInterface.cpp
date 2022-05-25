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

void UserInterface::printActionMenu()
{
	// Изменяем цвет фона на серый
	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	// Стартовый индекс печати главного меню действий
	int startIndex = 0;

	cout << listOfMenuItems[startIndex++] << endl;
	//cout << "Выберите действие: " << endl;

	cout << resetColorParams();

	// Печатаем пункты меню
	for (int i = startIndex; i < NUMBER_OF_MAIN_MENU_ITEMS; ++i)
	{
		cout << listOfMenuItems[i] << endl;
	}
		//<< "Создание зелий" << endl
		//<< "Покупка ингредиентов" << endl
		//<< "Продажа ингредиентов" << endl
		//<< "Продажа зелий" << endl
		//<< "Работа с таблицей" << endl;

	cout << goToXY(ACTION_MENU_Y_COORD, 1);

	// Запоминаем текущие координаты курсора
	this->currentXCursorCoord = 1;
	this->currentYCursorCoord = ACTION_MENU_Y_COORD;

	this->func = std::bind(&UserInterface::isArrowKeyFalse, this, _1);

	// Флаг для выхода из цикла do-while
	bool exitFlag = false;

	do {
		// Проверяем нажатую кнопку
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_UP:
			{
				// Проверяем стрелочки
				checkArrowsChoice(exitFlag, ACTION_MENU_Y_COORD, VK_UP);

				//if (ACTION_MENU_Y_COORD == this->currentYCursorCoord)
				//{
				//	exitFlag = true;
				//}
				//else
				//{
				//	cout << goToXY(--this->currentYCursorCoord, 1);
				//	// Изменяем цвет фона на серый
				//	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
				//	// печатаем главное меню действий
				//	for (int i = currentYCursorCoord; i < ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS; ++i)
				//	{
				//		if (i == currentYCursorCoord)
				//		{
				//			// Изменяем цвет фона на серый
				//			cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
				//			// Печатаем пункт меню
				//			cout << actionMenu[i] << endl; 
				//			// Сбрасываем параметры текста
				//			cout << resetColorParams();
				//		}
				//		else 
				//			// Печатаем пункт меню
				//			cout << actionMenu[i] << endl;
				//	}
				//	cout << goToXY(currentYCursorCoord, 1);
				//	// Сбрасываем флаг
				//	exitFlag = false;
				// }	
			}
			break;

			case VK_DOWN:
			{
				// Проверяем стрелочки
				checkArrowsChoice(exitFlag, ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN);
			}
			break;

			case VK_RETURN:
			{
				if (ACTION_MENU_Y_COORD == this->currentYCursorCoord)
				{
					exitFlag = false;
				}

				else
					// !! Осуществление действий
				{

				}
			}
		break;

			case VK_ESCAPE:
			break;			
		}
	} while (false == exitFlag);
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

//bool UserInterface::isContinueGameFalse(int key)
//{
//	return VK_1 != key && VK_2 != key && VK_NUMPAD1 != key && VK_NUMPAD2 != key && key != VK_ESCAPE;
//}

bool UserInterface::isContinue(int key)
{
	return VK_RETURN != key && VK_ESCAPE != key;
}

bool UserInterface::isArrowKeyFalse(int key)
{
	bool res = VK_UP != key && VK_DOWN != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

void UserInterface::setXCoord()
{
	titleXCoord = (calculateConsoleWidth() / 2) - (title.length() / 2);
}

//void UserInterface::fillActionMenuMap()
//{
//	// Стартовый ключ
//	int startIndex = ACTION_MENU_Y_COORD;
//
//	// Заполняем ассоциативный массив
//	for (int i = 0; i < NUMBER_OF_MAIN_MENU_ITEMS; ++i, ++startIndex)
//	{
//		this->actionMenu.emplace(startIndex, listOfMenuItems[i]);
//	}
//}

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

void UserInterface::checkArrowsChoice(bool &exitFlag, int BorderYCoord, int keyCode)
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
		for (int i = currentYCursorCoord; i < ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS; ++i)
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

//void UserInterface::checkExit()
//{
//	
//}

//void UserInterface::doAlchemy()
//{
//	//printContinueGameMenu();
//
//	// !!! Стерла всё, т.к. инфа будет парситься !!!
//
//	//cout << "Хотите продолжить последнюю игру или создать новую?" << endl
//	//	<< "1 - Продолжить игру" << endl
//	//	<< "2 - Создать новую игру" << endl;
//
//	//func = std::bind(&UserInterface::isContinueGameFalse, this, _1);
//
//	//checkMenuChoice();
//
//	// !!! Нужно спарсить
//	// Имя алхимика
//
//
//
//
//
//	// !!! СПАРСИЛИ !!!
//
//	// если имя пользователя пустое
//	if ("" == this->alchemist->getName())
//	{
//		// имя пользователя
//		string name;
//
//		cout << "Введите ваше имя: ";
//
//		cin >> name;
//
//		this->alchemist->setName(name);
//	}
//
//
//
//	//string name = "Андрей";
//
//	eraseScreenAfterTitle();
//
//	//this->alchemist->setName(name);
//
//	this->alchemist->print();
//
//	printActionMenu();
//
//}