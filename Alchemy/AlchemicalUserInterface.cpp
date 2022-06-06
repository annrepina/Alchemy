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

	this->ingredientsTableprinter = new IngredientsTablePrinter();
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
				checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
			}
			break;

			case VK_DOWN:
			{
				// Проверяем стрелочки
				checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
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

void AlchemicalUserInterface::choosePage(int page, TableCode code)
{
	this->func = std::bind(&AlchemicalUserInterface::isPageChoiceFalse, this, _1);

	// Флаг ддля выхода из цикла
	bool exit = false;

	do
	{
		// Проверяем нажатую кнопку
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_LEFT:
			{
				// Проверяем стрелочки
				//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
				//checkHorizontalArrowChoice(page, code, VK_LEFT);

				if (checkHorizontalArrowChoice(page, code, VK_LEFT))
				{
					printTablePagesInLoop(code, page);
					exit = true;
				}		
			}
			break;

			case VK_RIGHT:
			{
				// Проверяем стрелочки
				//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
				if (checkHorizontalArrowChoice(page, code, VK_RIGHT))
				{
					printTablePagesInLoop(code, page);
					exit = true;
				}
			}
			break;

			case VK_RETURN:
			{
				exit = true;
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag && false == exit);
}

int AlchemicalUserInterface::chooseId(string strChoice, TableCode code)
{
	int id = 0;

	string value = "";

	// перейти по координате для выбора
	cout << goToXY(Y_COORD_AFTER_MENU_TITLE, strChoice.size() + 1);

	map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

	//checkInput(id, 1, iter->first, strChoice);

	if (code == TableCode::IngredientsTable)
	{
		map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

		id = checkInput(value, 1, iter->first);
	}
	else
	{

	}

	return id;
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

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int& page, TableCode code, int keyCode)
{
	if (VK_LEFT == keyCode)
	{
		// если это не первая страница
		if (FIRST_PAGE < page)
		{
			--page;
			return true;
		}
			
		else
			return false;
	}

	else
	{
		// Если рассматриваем таблицу ингредиентов
		if (code == TableCode::IngredientsTable)
		{
			int numberOfLines = ingredientsTableprinter->getNumberOfLines();

			if (numberOfLines > page * NUMBER_OF_CONTENT_LINES)
			{
				++page;
				return true;
			}
			else
				return false;
		}

		// если рассматриваем таблицу зелий
		else 
		{

		}
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
	// начальная страница таблицы
	int page = FIRST_PAGE;

	string choice = "Введите id ингредиента: ";

	// Флаг ддля выхода из цикла
	bool exit = false;

	cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	printColoredText(choice, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);


	printTablePagesInLoop(TableCode::IngredientsTable, page);

	if (true == exitFlag)
		return;

	//do
	//{
	//	this->ingredientsTableprinter->print(this->alchemyProgram->getIngredientsTable(), page);

	//	printPageMenu(page);

	//	choosePage(page, TableCode::IngredientsTable, exit);

	//} while (false == exit);



	int id = chooseId(choice, TableCode::IngredientsTable);


	//// перейти по координате для выбора
	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE, choice.size() + 1);
	
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
	// Уменьшаем на 1 за счет рамки
	titleXCoord = calculateXCoordInMiddle(title) - 1;

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

	menuCode = MenuCode::InstructionsMenu;

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

void AlchemicalUserInterface::printPageMenu(int page)
{
	printColoredText("Страница " + to_string(page), R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	cout << "\t<-- Перейти на предыдущую страницу\t Перейти на следующую страницу -->\tENTER Подтвердить выбор страницы";
}

void AlchemicalUserInterface::printTablePagesInLoop(TableCode code, int& page)
{
	if (code == TableCode::IngredientsTable)
	{
		this->ingredientsTableprinter->print(this->alchemyProgram->getIngredientsTable(), page);

		printPageMenu(page);

		choosePage(page, TableCode::IngredientsTable);
	}
	else
	{

	}
}

bool AlchemicalUserInterface::isPageChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}
