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

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"Назад",
	"Выйти из программы"
};

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
	this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->instructionsXCoord = 0;
	this->instructionsTitle = "Инструкции к программе \"Зельеварение\"";
}

void AlchemicalUserInterface::launchMainLoop()
{
	mainMenu = fillActionMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillActionMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);

	this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	instructionsMenu = fillActionMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);

	// Возможно раскоментировать
	//setXCoord();

	printTitle();

	printExitButton();

	cout << endl;

	printAlchemist();

	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;

	menuCode = MenuCode::MainMenu;

	printMenuInLoop(mainMenu);

	printBye();
}

void AlchemicalUserInterface::chooseMenuItem(map <int, string> menu)
{
	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	do {
		// Проверяем нажатую кнопку
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_UP:
			{
				// Проверяем стрелочки
				checkArrowsChoice(boundaryYCoord, VK_UP, menu);
			}
			break;

			case VK_DOWN:
			{
				// Проверяем стрелочки
				checkArrowsChoice(boundaryYCoord + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, menu);
			}
			break;

			case VK_RETURN:
			{
				// Сделать выбор пункта меню
				makeChoice();// !! Осуществление действий
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag);
}

void AlchemicalUserInterface::makeChoice()
{
	switch (menuCode)
	{
		case MenuCode::MainMenu:
		{
			checkChoiceInMainMenu();
		}
		break;

		case MenuCode::AlchemicalMenu:
		{

		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkChoiceInInstructionsMenu();
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInMainMenu()
{
	switch (this->currentYCursorCoord)
	{
		case MainMenuCode::DoAlchemy:
		{
			doAlchemy();
		}
		break;

		case MainMenuCode::ReadInstructions:
		{
			printInstructions();
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInInstructionsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case InstructionsMenuCode::Return:
		{
			this->menuCode = MenuCode::MainMenu;
			this->currentYCursorCoord = MAIN_MENU_Y_COORD;
			this->boundaryYCoord = MAIN_MENU_Y_COORD;

			eraseScreenAfterAlchemist();

			printMenuInLoop(mainMenu);
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
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

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void AlchemicalUserInterface::printTitle()
{
	titleXCoord = calculateXCoordInMiddle(title);

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

void AlchemicalUserInterface::printMenuInLoop(map<int, string> menu)
{
	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenu(menu);

	cout << goToXY(currentYCursorCoord, STANDARD_CURSOR_X_COORD);
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	//eraseScreenAfterTitle();

	eraseScreenAfterAlchemist();

	this->instructionsXCoord = calculateXCoordInMiddle(instructionsTitle);

	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, instructionsXCoord);

	printColoredText(instructionsTitle, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	cout << endl;

	//printTextWithBackground("Назад", R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	menuCode = MenuCode::InstructionsMenu;
	
	this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	this->boundaryYCoord = INSTRUCTIONS_Y_COORD;

	printMenuInLoop(instructionsMenu);
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

	cout << goToXY(MAIN_MENU_Y_COORD, 1);

	//// Запоминаем текущие координаты курсора
	//this->currentXCursorCoord = 1;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;

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
			checkArrowsChoice(MAIN_MENU_Y_COORD, VK_UP, alchemicalMenu);

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
			checkArrowsChoice(MAIN_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, alchemicalMenu);
		}
		break;

		case VK_RETURN:
		{
			if (MAIN_MENU_Y_COORD == this->currentYCursorCoord)
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

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("До скорой встречи!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
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

	eraseScreenAfterTitle();

	this->alchemist->print();
}
