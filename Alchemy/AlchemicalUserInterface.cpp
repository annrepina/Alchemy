#include "AlchemicalUserInterface.h"

AlchemicalUserInterface::AlchemicalUserInterface() : UserInterface()
{
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->instructionsMenuTitle = "Инструкции к программе \"Зельеварение\"";
	this->mainMenuTitle = "Главное меню";
	this->alchemicalMenuTitle = "Меню алхимии";
	this->buyingIngredientsMenuTitle = "Покупка ингредиентов";
	this->buingFaultMenuTitle = "Недостаточно средств для покупки ингредиента №";

	// Программа - алхимия
	this->alchemyLogic = nullptr;

	// Строитель для алхимической программы
	this->alchemyLogicBuilder = new AlchemyLogicBuilder();

	// создаем новый экземпляр
	this->alchemyProgramParser = new AlchemyProgramParser();

	this->ingredientsTableprinter = new IngredientsTablePrinter();
	this->potionTablePrinter = new PotionTablePrinter();

	this->state = new MainMenuState(this);
}

void AlchemicalUserInterface::launchMainLoop()
{
	setAlchemyLogic();

	//fillAllMenu();

	// Передаем в принтер таблицу
	this->ingredientsTableprinter->setTable(this->alchemyLogic->getIngredientsTable());
	this->potionTablePrinter->setTable(this->alchemyLogic->getPotionTable());

	// Считаем данные по таблице 
	this->ingredientsTableprinter->calculateData();

	/*if(this->alchemyLogic->getPotionTable()->getStartIterator() != this->alchemyLogic->getPotionTable()->getEndIterator())*/
		this->potionTablePrinter->calculateData();

	// Заполняем таблицу контентом
	this->ingredientsTableprinter->fillInTableContent();
	this->potionTablePrinter->fillInTableContent();

	// Добавляем подписчиков
	this->alchemyLogic->getIngredientsTable()->subscribe(this->ingredientsTableprinter);

	printTitle();

	printExitButton();

	do
	{
		printAlchemist();

		//menuCode = MenuCode::MainMenu;

		//// Сбрасываем по умолчанию координату
		//this->currentYCursorCoord = MAIN_MENU_Y_COORD;

		// Вытащила из принтМенюТайтл
		eraseScreenAfterAlchemist();

		//this->state->setListOfStates();

		this->state->printMenu();

		//printMenuInLoop(mainMenu, mainMenuTitle);

	} while (exitFlag == false);

	printBye();
}

int AlchemicalUserInterface::getBoundaryYCoord()
{
	return this->boundaryYCoord;
}

bool AlchemicalUserInterface::getExitFlag()
{
	return this->exitFlag;
}

AlchemyLogic* AlchemicalUserInterface::getAlchemyLogic()
{
	return this->alchemyLogic;
}

void AlchemicalUserInterface::setState(MenuState* state)
{
	if (state != nullptr)
	{
		if (this->state != nullptr)
		{
			delete this->state;
			this->state = nullptr;
		}

		this->state = state;
	}
}

void AlchemicalUserInterface::setExitFlag(bool exit)
{
	this->exitFlag = exit;
}

void AlchemicalUserInterface::setAlchemyLogic()
{
	// Создать программу Алхимии
	this->alchemyLogicBuilder->buildAlchemyProgram(this->alchemyProgramParser);

	// Присвоить результат программе алхимии
	this->alchemyLogic = this->alchemyLogicBuilder->getResult();
}

//void AlchemicalUserInterface::chooseMenuItem(map <int, string> menu)
//{
//	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);
//
//	// Флаг для возвращения в предыдущее меню, но не выход из программы
//	bool innerExitFlag = false;
//
//	do {
//		// Проверяем нажатую кнопку
//		checkMenuChoice();
//
//		switch (this->keyBoard->getPressedKey())
//		{
//			case VK_UP:
//			{
//				// Проверяем стрелочки
//				//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
//			}
//			break;
//
//			case VK_DOWN:
//			{
//				// Проверяем стрелочки
//				//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
//			}
//			break;
//
//			case VK_RETURN:
//			{
//				//// Сделать выбор пункта меню
//				//makeChoice(innerExitFlag);// !! Осуществление действий
//			}
//			break;
//
//			case VK_ESCAPE:
//			{
//				exitFlag = true;
//			}
//			break;
//		}
//	} while (false == exitFlag && false == innerExitFlag);
//}

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

				//this->setState(this->state->getNextState());
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
	cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, strChoice.size() + 1);

	//map<int, Ingredient*>::iterator iter = --this->alchemyLogic->getIngredientsTable()->getEndIterator();

	//checkInput(id, 1, iter->first, strChoice);

	if (code == TableCode::IngredientTable)
	{
		map<int, Ingredient*>::iterator iter = --this->alchemyLogic->getIngredientsTable()->getEndIterator();

		string errorText = "Данного значения не существует в таблице, попробуйте снова: ";

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_2);
	}
	else
	{

	}

	return id;
}

int AlchemicalUserInterface::chooseNumber(string strChoice, TableCode code, int yCoord)
{
	int number = 0;

	string value = "";

	if (code == TableCode::IngredientTable)
	{
		// перейти по координате для выбора
		cout << goToXY(yCoord, strChoice.size() + 1);

		//map<int, Ingredient*>::iterator iter = this->alchemyLogic->getIngredientsTable()->getEndIterator();

		string errorText = "Данное значение не подходит, попробуйте снова: ";

		number = checkInput(value, 1, MAX_INT, errorText, yCoord);
	}
	else
	{

	
	}

	return number;
}

//void AlchemicalUserInterface::makeChoice(bool& innerExitFlag)
//{
//	switch (menuCode)
//	{
//		case MenuCode::MainMenu1:
//		{
//			checkMainMenu(innerExitFlag);
//		}
//		break;
//
//		case MenuCode::AlchemicalMenu:
//		{
//			checkAlchemicalMenu(innerExitFlag);
//		}
//		break;
//
//		case MenuCode::InstructionsMenu:
//		{
//			checkInstructionsMenu(innerExitFlag);
//		}
//		break;
//
//		case MenuCode::BuyingIngredientsMenu:
//		{
//			checkBuyingIngredientsMenu(innerExitFlag);
//		}
//		break;
//
//		case MenuCode::BuyingFaultMenu:
//		{
//			checkBuyingFaultMenu();
//		}
//	}
//}

//void AlchemicalUserInterface::makeChoice()
//{
//
//}

//void AlchemicalUserInterface::checkMainMenu(bool& innerExitFlag)
//{
//	switch (this->currentYCursorCoord)
//	{
//		case MainMenuCode::DoAlchemy:
//		{
//			doAlchemy();
//		}
//		break;
//
//		case MainMenuCode::ReadInstructions:
//		{
//			printInstructions();
//		}
//		break;
//	}
//
//	innerExitFlag = true;
//}

//void AlchemicalUserInterface::checkInstructionsMenu(bool& innerExitFlag)
//{
//	switch (this->currentYCursorCoord)
//	{
//		case InstructionsMenuCode::InstrReturn:
//		{
//			//this->menuCode = MenuCode::MainMenu;
//			//this->currentYCursorCoord = MAIN_MENU_Y_COORD;
//
//			//eraseScreenAfterAlchemist();
//
//			//printMenuInLoop(mainMenu, mainMenuTitle);
//
//			innerExitFlag = true;
//		}
//		break;
//
//		case InstructionsMenuCode::Exit:
//		{
//			this->exitFlag = true;
//		}
//		break;
//	}
//}

//void AlchemicalUserInterface::checkAlchemicalMenu(bool& innerExitFlag)
//{
//	switch (this->currentYCursorCoord)
//	{
//		case AlchemicalMenuCode::MakingPotions:
//		{
//
//		}
//		break;
//
//		case AlchemicalMenuCode::BuyingIngredients:
//		{
//			buyIngredients();
//		}
//		break;
//
//
//
//		case AlchemicalMenuCode::AlcReturn:
//		{
//			innerExitFlag = true;
//		}
//		break;
//	}
//}

//void AlchemicalUserInterface::checkBuyingIngredientsMenu(bool& innerExitFlag)
//{
//	switch (this->currentYCursorCoord)
//	{
//		case BuyingIngredientsMenuCode::ChooseFromList:
//		{
//			buyIngredientsFromList();
//		}
//		break;
//
//		case BuyingIngredientsMenuCode::CreateNewIngredient:
//		{
//
//		}
//		break;
//	}
//
//	innerExitFlag = true;
//}

//void AlchemicalUserInterface::checkBuyingFaultMenu()
//{
//	switch (this->currentYCursorCoord)
//	{
//		case BuyingFaultMenuCode::СhooseAnotherIngredient:
//		{
//			//chooseAnotherIngredient();
//		}
//		break;
//
//		case BuyingFaultMenuCode::ChangeNumberOfIngredient:
//		{
//			//changeNumberOfIngredient();
//		}
//		break;
//	}
//}

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
		if (code == TableCode::IngredientTable)
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

//void AlchemicalUserInterface::doAlchemy()
//{
//	// Флаг для выхода из цикла
//	bool innerExitFlag = false;
//
//	do
//	{
//		this->currentYCursorCoord = MAIN_MENU_Y_COORD;
//
//		this->menuCode = MenuCode::AlchemicalMenu;
//
//		printMenuInLoop(alchemicalMenu, alchemicalMenuTitle);
//
//	} while (exitFlag == false && innerExitFlag == false);
//}

//void AlchemicalUserInterface::buyIngredients()
//{
//	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
//	//this->boundaryYCoord = MAIN_MENU_Y_COORD;
//
//	this->menuCode = MenuCode::BuyingIngredientsMenu;
//
//	printMenuInLoop(buyingIngredientsMenu, alchemicalMenuTitle);
//}

//void AlchemicalUserInterface::buyIngredientsFromList()
//{
//	// начальная страница таблицы
//	int page = FIRST_PAGE;
//
//	string choiceIngredient = "Введите № ингредиента: ";
//
//	string choiceNumber = "Введите кол-во ингредиентов: ";
//
//	// Флаг ддля выхода из цикла
//	bool exit = false;
//
//	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);
//
//	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);
//
//	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
//
//	//printColoredText(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
//
//	printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);
//
//	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE + 1, STANDARD_CURSOR_X_COORD);
//
//	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
//
//	//printColoredText(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
//
//	printTablePagesInLoop(TableCode::IngredientTable, page);
//
//	// если был нажат esc
//	if (true == exitFlag)
//		return;
//
//	// Выбор id (номера) ингредиента
//	int id = chooseId(choiceIngredient, TableCode::IngredientTable);
//
//	// Выбор кол-ва ингредиентов
//	int number = chooseNumber(choiceNumber, TableCode::IngredientTable);
//
//	tryAddIngredientFromList(id, number);
//
//
//	
//}

//bool AlchemicalUserInterface::tryAddIngredientFromList(int id, int number)
//{
//	// результат
//	bool res = false;
//
//	// таблица ингредиентов
//	IngredientsTable* ingredientsTable = this->alchemyLogic->getIngredientsTable();
//
//	// Этот ингредиент, полученный по id 
//	Ingredient* ingredient = ingredientsTable->getIngredientById(id);
//
//	// Получаем алхимика
//	Alchemist* alchemist = this->alchemyLogic->getAlchemist();
//
//	// деньги алхимика
//	int capital = alchemist->getCapital();
//
//	// расходы
//	int cost = ingredient->getPrice() * number;
//
//	// если денег у алхимика больше или равно цене ингредиента
//	if (capital >= cost)
//	{
//		ingredient->increaseNumber(number);
//
//		// уведомляем подписчиков об изменениях
//		ingredientsTable->notify(id);
//
//		alchemist->decreaseCapital(cost);
//
//		res = true;
//	}
//	// если денег недостаточно
//	else
//	{
//		//this->currentYCursorCoord = MAIN_MENU_Y_COORD;
//
//		//// Создаем название меню
//		//string menuTitle = this->buingFaultMenuTitle + to_string(id);
//
//		//MenuCode menuCode = MenuCode::BuyingFaultMenu;
//
//		//printMenuInLoop(buyingFaultMenu, menuTitle);
//
//		res = false;
//	}
//
//	return res;
//}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

//void AlchemicalUserInterface::fillAllMenu()
//{
//	mainMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
//	alchemicalMenu = fillMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);
//	instructionsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);
//	buyingIngredientsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingIngredientsMenuItems);
//	this->buyingFaultMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingFaultMenuItems/* Y_COORD_AFTER_MENU_TITLE_4*/);
//}

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
	
	//chooseMenuItem(menu);
}

//void AlchemicalUserInterface::printInstructions()
//{
//	menuCode = MenuCode::InstructionsMenu;
//
//	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
//
//	printMenuInLoop(instructionsMenu, instructionsMenuTitle);
//}

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("До скорой встречи!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

void AlchemicalUserInterface::printAlchemist()
{
	// Если файл пустой и имя пустое
	if ("" == this->alchemyLogic->getAlchemist()->getName())
	{
		string name;

		cout << "Введите ваше имя: ";
		cin >> name;

		this->alchemyLogic->getAlchemist()->setName(name);
	}

	eraseScreenAfterTitle();

	this->alchemyLogic->getAlchemist()->print();
}

void AlchemicalUserInterface::printMenuTitle(string title)
{
	//eraseScreenAfterAlchemist();

	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(this->currentYCursorCoord - TWO_LINES, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}

void AlchemicalUserInterface::printPageMenu(int page)
{
	string strPage = "Страница " + to_string(page + 1);

	int numberOfSymbols = strPage.size();

	cout << goToXY(PAGE_Y_COORD, 0);

	cout << eraseSymbolsOnScreen(to_string(numberOfSymbols));

	printColoredText("Страница " + to_string(page), R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	cout << "\t<-- Перейти на предыдущую страницу\t Перейти на следующую страницу -->\tENTER Подтвердить выбор страницы\t ESC - назад";
}

void AlchemicalUserInterface::printTablePagesInLoop(TableCode code, int& page)
{
	if (code == TableCode::IngredientTable)
	{
		this->ingredientsTableprinter->print(page);

		printPageMenu(page);

		choosePage(page, TableCode::IngredientTable);
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
