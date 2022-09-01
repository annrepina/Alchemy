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
	this->alchemyLogic->getPotionTable()->subscribe(this->potionTablePrinter);

	printTitle();

	printExitButton();

	do
	{
		printAlchemist();

		// Вытащила из принтМенюТайтл
		eraseScreenAfterAlchemist();

		this->state->printMenu();

	} while (exitFlag == false);

	printBye();
}

#pragma region Геттеры

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

IngredientsTablePrinter* AlchemicalUserInterface::getIngredientsTablePrinter()
{
	return this->ingredientsTableprinter;
}

PotionTablePrinter* AlchemicalUserInterface::getPotionTablePrinter()
{
	return this->potionTablePrinter;
}

#pragma endregion Геттеры

#pragma region Сеттеры

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

#pragma endregion Сеттеры

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

void AlchemicalUserInterface::choosePageWhileSorting(vector<vector<string>> content, int page, TableCode code, int numberOfColumn, bool orderOfSorting)
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
			if (checkHorizontalArrowChoice(content.size(), page, code, VK_LEFT))
			{
				printTablePagesInLoopWhileSorting(content, code, page, numberOfColumn, orderOfSorting);
				//printTablePagesInLoop(code, page);
				exit = true;
			}
		}
		break;

		case VK_RIGHT:
		{
			// Проверяем стрелочки
			if (checkHorizontalArrowChoice(content.size(), page, code, VK_RIGHT))
			{
				printTablePagesInLoopWhileSorting(content, code, page, numberOfColumn, orderOfSorting);
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

			//exit = true;
			exitFlag = true;

			//this->setState(this->state->getNextState());
		}
		break;
		}
	} while (false == exitFlag && false == exit);
}

void AlchemicalUserInterface::choosePageFromAvailableContent(int page, TableCode code)
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
			if (checkHorizontalArrowChoice(page, code, VK_LEFT))
			{
				printTableWithAvailableToUserElements(code, page);
				exit = true;
			}
		}
		break;

		case VK_RIGHT:
		{
			// Проверяем стрелочки
			if (checkHorizontalArrowChoice(page, code, VK_RIGHT))
			{
				printTableWithAvailableToUserElements(code, page);
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

void AlchemicalUserInterface::chooseColumnAndOrderOfSorting(int& numberOfColumn, bool& orderOfSorting, TableCode code)
{
	this->func = std::bind(&AlchemicalUserInterface::isColumnAndOrderChoiceFalse, this, _1);

	// Флаг ддля выхода из цикла
	bool exit = false;

	int page = FIRST_PAGE;

	do
	{
		// Проверяем нажатую кнопку
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_LEFT:
			{
				if (checkHorizontalArrowChoice(numberOfColumn, VK_LEFT, code))
					exit = true;
			}
			break;

			case VK_RIGHT:
			{
				// Проверяем стрелочки
				if (checkHorizontalArrowChoice(numberOfColumn, VK_RIGHT, code))
					exit = true;
			}
			break;

			case VK_DOWN:
			{
				if (checkVerticalArrowChoice(orderOfSorting, VK_DOWN, code))
					exit = true;

			}
			break;

			case VK_UP:
			{
				if (checkVerticalArrowChoice(orderOfSorting, VK_UP, code))
					exit = true;
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

void AlchemicalUserInterface::chooseColumnForFiltration(int& numberOfColumn, TableCode code)
{

}

void AlchemicalUserInterface::chooseExit()
{
	this->func = std::bind(&AlchemicalUserInterface::isEscKeyFalse, this, _1);

	do
	{
		// Проверяем нажатую кнопку
		checkMenuChoice();

		if (this->keyBoard->getPressedKey() == VK_ESCAPE)
		{
			exitFlag = true;
		}

	} while (false == exitFlag);
}

int AlchemicalUserInterface::chooseId(TableCode code)
{
	int id = 0;

	string value = "";

	if (code == TableCode::IngredientTable)
	{
		auto iter = --this->alchemyLogic->getIngredientsTable()->getEndIterator();

		string errorText = "Данного значения не существует в таблице, попробуйте снова: ";

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_2);
	}
	else
	{
		auto iter = --this->alchemyLogic->getPotionTable()->getEndIterator();

		string errorText = "Данного значения не существует в таблице, попробуйте снова: ";

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_2);
	}

	return id;
}

int AlchemicalUserInterface::chooseIdFromAvailableElements(string strChoice, TableCode code)
{
	return 0;
}

int AlchemicalUserInterface::chooseNumber(string strChoice, int yCoord)
{
	int number = 0;

	string value = "";

	// перейти по координате для выбора
	cout << goToXY(yCoord, strChoice.size() + 1);

	string errorText = "Данное значение не подходит, попробуйте снова: ";

	number = checkInput(value, 1, MAX_INT, errorText, yCoord);

	return number;
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
		int numberOfLines;

		// Если рассматриваем таблицу ингредиентов
		if (code == TableCode::IngredientTable)
			numberOfLines = ingredientsTableprinter->getNumberOfLines();

		// если рассматриваем таблицу зелий
		else 
			numberOfLines = potionTablePrinter->getNumberOfLines();


		if (numberOfLines > page * NUMBER_OF_CONTENT_LINES)
		{
			++page;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int contentSize, int& page, TableCode code, int keyCode)
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
		if (contentSize > page * NUMBER_OF_CONTENT_LINES)
		{
			++page;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int& numberOfColums, int keyCode, TableCode code)
{
	if (VK_LEFT == keyCode)
	{
		// если это не первая колонка
		if (DEFAULT_NUMBER_OF_COLUMN < numberOfColums)
		{
			--numberOfColums;
			return true;
		}

		else
			return false;
	}

	else
	{
		int totalNumberOfColumns;

		// Если рассматриваем таблицу ингредиентов
		if (code == TableCode::IngredientTable)
			totalNumberOfColumns = ingredientsTableprinter->getNumberOfColumns();

		// если рассматриваем таблицу зелий
		else
			totalNumberOfColumns = potionTablePrinter->getNumberOfColumns();

		// если это не последняя колонка
		if (totalNumberOfColumns > numberOfColums)
		{
			++numberOfColums;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkVerticalArrowChoice(bool& orderOfSorting, int keyCode, TableCode code)
{
	if (VK_UP == keyCode)
	{
		// если это уже не сортировка по возрастанию
		if (ASCENDING_ORDER_OF_SORTING != orderOfSorting)
		{
			orderOfSorting = ASCENDING_ORDER_OF_SORTING;
			return true;
		}

		else
			return false;
	}

	else
	{
		// если это уже не сортировка по убыванию
		if (DESCENDING_ORDER_OF_SORTING != orderOfSorting)
		{
			orderOfSorting = DESCENDING_ORDER_OF_SORTING;
			return true;
		}
		else
			return false;
	}
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

#pragma region Методы печати

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
		this->ingredientsTableprinter->print(page);

	else
		this->potionTablePrinter->print(page);

	printPageMenu(page);

	choosePage(page, code);
}

void AlchemicalUserInterface::printTablePagesInLoopWhileSorting(vector<vector<string>> content, TableCode code, int& page, int numberOfColumn, bool orderOfSorting)
{
	if (code == TableCode::IngredientTable)
		this->ingredientsTableprinter->print(content, page, numberOfColumn, orderOfSorting);

	else
		this->potionTablePrinter->print(content, page, numberOfColumn, orderOfSorting);

	printPageMenu(page);

	choosePageWhileSorting(content, page, code, numberOfColumn, orderOfSorting);
}

void AlchemicalUserInterface::printTableWithAvailableToUserElements(TableCode code, int& page)
{
	if (code == TableCode::IngredientTable)
	{
		if (this->ingredientsTableprinter->getNumberOfAvailableContent() <= (page - 1) * NUMBER_OF_CONTENT_LINES)
			return;

		this->ingredientsTableprinter->printAvailableElements(page);

		printPageMenu(page);

		choosePageFromAvailableContent(page, TableCode::IngredientTable);
	}
	else
	{

	}
}

void AlchemicalUserInterface::printFirstTablePage(TableCode code)
{
	if (code == TableCode::IngredientTable)
	{
		this->ingredientsTableprinter->printAvailableElements(FIRST_PAGE);
	}
	else
	{

	}

}

#pragma endregion Методы печати

bool AlchemicalUserInterface::isPageChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

bool AlchemicalUserInterface::isColumnAndOrderChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key && VK_UP != key && VK_DOWN != key;

	return res;
}


