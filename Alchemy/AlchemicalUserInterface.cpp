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
	"Поедание ингредиентов",
	"Продажа зелий",
	"Работа с таблицами"
};

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"Назад",
	"Выйти из программы"
};

string AlchemicalUserInterface::listOfBuyingIngredientsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"Покупка ингредиентов из имеющегося списка",
	"Покупка новых ингредиентов, которых нет в списке"
};

AlchemicalUserInterface::AlchemicalUserInterface() : UserInterface()
{
	//this->alchemist = new Alchemist();
	//this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	//this->instructionsXCoord = 0;
	this->instructionsMenuTitle = "Инструкции к программе \"Зельеварение\"";
	this->mainMenuTitle = "Главное меню";
	this->alchemicalMenuTitle = "Меню алхимии";
	this->buyingIngredientsMenuTitle = "Покупка ингредиентов";

	// Программа - алхимия
	this->alchemyProgram = nullptr;

	// Строитель для алхимической программы
	this->alchemyProgramBuilder = new AlchemyProgramBuilder();

	// создаем новый экземпляр
	this->alchemyProgramParser = new AlchemyProgramParser();
}

void AlchemicalUserInterface::launchMainLoop()
{
	setAlchemyProgram();

	fillAllMenu();

	printTitle();

	printExitButton();

	printAlchemist();

	menuCode = MenuCode::MainMenu;

	printMenuInLoop(mainMenu, mainMenuTitle);

	printBye();
}

void AlchemicalUserInterface::setAlchemyProgram()
{
	// Создать программу Алхимии
	this->alchemyProgramBuilder->buildAlchemyProgram(this->alchemyProgramParser);

	// Присвоить результат программе алхимии
	this->alchemyProgram = this->alchemyProgramBuilder->getResult();
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
				checkArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
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
			checkMainMenu();
		}
		break;

		case MenuCode::AlchemicalMenu:
		{
			checkAlchemicalMenu();
		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkInstructionsMenu();
		}
		break;

		case MenuCode::BuyingIngredientsMenu:
		{
			checkBuyingIngredientsMenu();
		}
		break;
	}
}

void AlchemicalUserInterface::checkMainMenu()
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

void AlchemicalUserInterface::checkInstructionsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case InstructionsMenuCode::Return:
		{
			this->menuCode = MenuCode::MainMenu;
			this->currentYCursorCoord = MAIN_MENU_Y_COORD;
			//this->boundaryYCoord = MAIN_MENU_Y_COORD;

			eraseScreenAfterAlchemist();

			printMenuInLoop(mainMenu, mainMenuTitle);
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::checkAlchemicalMenu()
{
	switch (this->currentYCursorCoord)
	{
		case AlchemicalMenuCode::MakingPotions:
		{

		}
		break;

		case AlchemicalMenuCode::BuyingIngredients:
		{
			buyIngredients();
		}
		break;
	}
}

void AlchemicalUserInterface::checkBuyingIngredientsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case BuyingIngredientsMenuCode::ChooseFromList:
		{
			buyIngredientsFromList();
		}
		break;

		case BuyingIngredientsMenuCode::CreateNewIngredient:
		{

		}
		break;
	}
}

void AlchemicalUserInterface::doAlchemy()
{
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::AlchemicalMenu;

	printMenuInLoop(alchemicalMenu, alchemicalMenuTitle);
}

void AlchemicalUserInterface::buyIngredients()
{
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::BuyingIngredientsMenu;

	printMenuInLoop(buyingIngredientsMenu, alchemicalMenuTitle);
}

void AlchemicalUserInterface::buyIngredientsFromList()
{
	cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);

	cout << "Введите id ингредиента: ";



	int id;

	cin >> id;
	
	
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void AlchemicalUserInterface::fillAllMenu()
{
	mainMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);
	instructionsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);
	buyingIngredientsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingIngredientsMenuItems);
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
	cout << goToXY(EXIT_Y_COORD, xCoord) << exit << endl << endl;
}

void AlchemicalUserInterface::printMenuInLoop(map<int, string> menu, string menuTitle)
{
	printMenuTitle(menuTitle);

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenu(menu);

	cout << goToXY(currentYCursorCoord, STANDARD_CURSOR_X_COORD);
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	//eraseScreenAfterAlchemist();

	//this->instructionsXCoord = calculateXCoordInMiddle(instructionsMenuTitle);

	//cout << goToXY(Y_COORD_AFTER_ALCHEMIST, instructionsXCoord);

	//printColoredText(instructionsMenuTitle, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	//cout << endl;

	menuCode = MenuCode::InstructionsMenu;
	
	//this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	//this->boundaryYCoord = INSTRUCTIONS_Y_COORD;

	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	printMenuInLoop(instructionsMenu, instructionsMenuTitle);
}

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("До скорой встречи!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

void AlchemicalUserInterface::printAlchemist()
{
	// Если файл пустой и имя пустое
	if ("" == this->alchemyProgram->getAlchemist()->getName())
	{
		string name;

		cout << "Введите ваше имя: ";
		cin >> name;

		this->alchemyProgram->getAlchemist()->setName(name);
	}

	eraseScreenAfterTitle();

	this->alchemyProgram->getAlchemist()->print();
}

void AlchemicalUserInterface::printMenuTitle(string title)
{
	eraseScreenAfterAlchemist();

	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	cout << endl;
}
