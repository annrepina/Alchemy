#include "AlchemicalUserInterface.h"

string AlchemicalUserInterface::listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"Алхимичить",
	"Читать инструкцию к программе"
};

// Возможно добавить меню "Перейти в инструкцию"
string AlchemicalUserInterface::listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS] = {
	"Создание зелий",
	"Покупка ингредиентов",
	"Продажа ингредиентов",
	"Продажа зелий",
	"Работа с таблицами"
};

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
	this->ingredientBuilder = new IngredientBuilder();
}

void AlchemicalUserInterface::launchMainLoop()
{
	fillActionMenuMap(MENU_Y_COORD, NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems, mainMenu);
	fillActionMenuMap(MENU_Y_COORD, NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems, alchemicalMenu);

	// Возможно раскоментировать
	//setXCoord();

	printTitle();

	printExitButton();

	cout << endl;

	printAlchemist();



	printMainMenu();

	this->func = std::bind(&AlchemicalUserInterface::isMenuChoiceFalse, this, _1);

	checkMenuChoice();

	eraseScreenAfterTitle();

	switch (this->keyBoard->getPressedKey())
	{
	case VK_1: case VK_NUMPAD1:
	{
		doAlchemy();
	}
	break;

	case VK_2: case VK_NUMPAD2:
	{
		cout << "\nИнструкция" << endl;
	}
	break;

	case VK_ESCAPE:
	{
		cout << "\nДо скорой встречи!" << endl;
	}
	break;
	}
}

void AlchemicalUserInterface::doAlchemy()
{
	//printContinueGameMenu();

// !!! Стерла всё, т.к. инфа будет парситься !!!

//cout << "Хотите продолжить последнюю игру или создать новую?" << endl
//	<< "1 - Продолжить игру" << endl
//	<< "2 - Создать новую игру" << endl;

//func = std::bind(&UserInterface::isContinueGameFalse, this, _1);

//checkMenuChoice();

// !!! Нужно спарсить
// Имя алхимика





// !!! СПАРСИЛИ !!!

// если имя пользователя пустое
	if ("" == this->alchemist->getName())
	{
		// имя пользователя
		string name;

		cout << "Введите ваше имя: ";

		cin >> name;

		this->alchemist->setName(name);
	}



	//string name = "Андрей";

	eraseScreenAfterTitle();

	//this->alchemist->setName(name);

	this->alchemist->print();

	printActionMenu();
}

void AlchemicalUserInterface::printTitle()
{
	this->setXCoord();

	printFramedText(title, TITLE_Y_COORD, titleXCoord);
}

void AlchemicalUserInterface::printExitButton()
{
	// Текст кнопки
	string exit = "ESC - выход";

	// координата печати кнопки
	int xCoord = calculateConsoleWidth() - exit.length();

	// Печать кнопки
	cout << goToXY(EXIT_Y_COORD, xCoord) << exit << endl;
}

void AlchemicalUserInterface::printMainMenu()
{
	cout << "\nВыберите действие: " << endl
		<< "1 - Алхимичить" << endl
		<< "2 - Ознакомиться с инструкцией к программе" << endl/*
		<< "ESC - выход" << endl*/;
}

void AlchemicalUserInterface::printInstructions()
{
	eraseScreenAfterTitle();

	cout << "Инструкции к программе \"Зельеварение\"" << endl
		<< "0 - назад"
		<< "ESC - выход";
}

void AlchemicalUserInterface::printActionMenu()
{
	// Изменяем цвет фона на серый
	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	//// Стартовый индекс печати главного меню действий
	//int startIndex = 0;

	//cout << listOfMenuItems[startIndex++] << endl;
	cout << "Выберите действие: " << endl;

	cout << resetColorParams();

	// Печатаем пункты меню
	for (int i = 0; i < NUMBER_OF_ALCHEMICAL_MENU_ITEMS; ++i)
	{
		cout << listOfALchemicalMenuItems[i] << endl;
	}
	//<< "Создание зелий" << endl
	//<< "Покупка ингредиентов" << endl
	//<< "Продажа ингредиентов" << endl
	//<< "Продажа зелий" << endl
	//<< "Работа с таблицей" << endl;

	cout << goToXY(MENU_Y_COORD, 1);

	// Запоминаем текущие координаты курсора
	this->currentXCursorCoord = 1;
	this->currentYCursorCoord = MENU_Y_COORD;

	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	// Флаг для выхода из цикла do-while
	bool exitFlag = false;

	do {
		// Проверяем нажатую кнопку
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
		case VK_UP:
		{
			// !! раскоментить
			// Проверяем стрелочки
			checkArrowsChoice(exitFlag, MENU_Y_COORD, VK_UP, alchemicalMenu);

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
			// !! раскоментить
			// Проверяем стрелочки
			checkArrowsChoice(exitFlag, MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, alchemicalMenu);
		}
		break;

		case VK_RETURN:
		{
			if (MENU_Y_COORD == this->currentYCursorCoord)
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

void AlchemicalUserInterface::printAlchemist()
{
	// ПАРСИМ!

	string name;

	// Если файл пустой и имя пустое
	if ("" == this->alchemist->getName())
	{
		cout << "Введите ваше имя: ";
		cin >> name;
	}

	this->alchemist->setName(name);

	cout << goToXY(Y_COORD_AFTER_TITLE, 0)
		 << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	this->alchemist->print();
}
