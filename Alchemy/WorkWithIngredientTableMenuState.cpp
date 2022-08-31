#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState()
{
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
}

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Работа с ингредиентами";
	this->goToTitle = "Работать с ингредиентами";
	this->numberOfStates = 1;
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithIngredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setListOfInnerMenuItems();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	setContent();

	// начальная страница таблицы
	int page = FIRST_PAGE;

	printMenuTitle();

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem();

		//// сбрасываем флаг после выбора поиск/сортировка
		//this->alchemicalUserInterface->setExitFlag(false);

		// если была нажата кнопка назад
		if (currentYCursorCoordState == MAIN_MENU_Y_COORD + INNER_MENU_ITEMS - 1)
		{
			// сбрасываем координату
			this->currentYCursorCoordState = MAIN_MENU_Y_COORD;

			this->alchemicalUserInterface->setState(this->getNextState());

			return;
		}

		int operationCode = defineOperation();

		workWithTable((OperationCode)operationCode);
	}
}

MenuState* WorkWithIngredientTableMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void WorkWithIngredientTableMenuState::setListOfStates()
{
	this->listOfCreatingFunctions.push_back(&WorkWithIngredientTableMenuState::createReturnMenuState);
}

void WorkWithIngredientTableMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&WorkWithIngredientTableMenuState::createReturnMenuState);
	}
}

void WorkWithIngredientTableMenuState::setContent()
{
	this->initialContent = this->ingredientTablePrinter->getTableContent();

	this->contentAfterSortingAndSearch = this->initialContent;
}

ReturnMenuState* WorkWithIngredientTableMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void WorkWithIngredientTableMenuState::printMenuItems()
{
	int border = this->boundaryYCoord + innerMenuItems.size();

	// Печатаем ассоциативный массив
	for (int i = this->currentYCursorCoordState; i < border; ++i)
	{
		if (i == this->currentYCursorCoordState)
		{
			printTextWithBackground(innerMenuItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// Печатаем пункт меню
			cout << innerMenuItems[i] << endl;
	}
}

void WorkWithIngredientTableMenuState::checkVerticalArrowsChoice(int borderYCoord, int keyCode)
{
		// если граничная координата не равна текущей
	if (borderYCoord != this->currentYCursorCoordState)
	{
		// Если кнопка вниз
		if (VK_DOWN == keyCode)
		{
			cout << goToXY(currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

			// Печатаем пункт меню без выделения
			cout << innerMenuItems[currentYCursorCoordState];

			// увеличиваем координаты
			++this->currentYCursorCoordState;
		}
		// если кнопка вверх
		else
			// уменьшаем координаты
			--this->currentYCursorCoordState;

		// Переходим по координатам
		cout << goToXY(this->currentYCursorCoordState, 0);

		printMenuItems();

		// Возвращаемся в координаты
		cout << goToXY(currentYCursorCoordState, 0);
	}
}

void WorkWithIngredientTableMenuState::chooseMenuItem()
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	// Флаг для выхода из цикла, но не выход из программы
	bool innerExitFlag = false;

	do
	{
		// Проверяем нажатую кнопку
		this->alchemicalUserInterface->checkMenuChoice();

		switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
		{
		case VK_UP:
		{
			this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);

		}
		break;

		case VK_DOWN:
		{
			// Проверяем стрелочки
			this->checkVerticalArrowsChoice(this->boundaryYCoord + innerMenuItems.size() - 1, VK_DOWN);
		}
		break;

		case VK_RETURN:
		{
			// выход из цикла
			innerExitFlag = true;
		}
		break;

		case VK_ESCAPE:
		{
			this->alchemicalUserInterface->setExitFlag(true);
			//exitFlag = true;
		}
		break;
		}
	} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
}

void WorkWithIngredientTableMenuState::setListOfInnerMenuItems()
{
	// если вектор пустой
	if (this->listOfInnerMenuItems.empty())
	{
		this->listOfInnerMenuItems.push_back("Сортировка");
		this->listOfInnerMenuItems.push_back("Поиск");
		this->listOfInnerMenuItems.push_back("Назад");
	}
}

int WorkWithIngredientTableMenuState::defineOperation()
{
	int operationCode = currentYCursorCoordState - MAIN_MENU_Y_COORD;

	return operationCode;
}

void WorkWithIngredientTableMenuState::workWithTable(OperationCode operationCode)
{
	switch (operationCode)
	{
		case OperationCode::Search:
		{

		}
		break;

		case OperationCode::Sorting:
		{
			sortData();
		}
		break;
	}
}

void WorkWithIngredientTableMenuState::sortData()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		// делаем выбор
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		// если критерий цифровой
		if (numberOfColumn == COLUMN_1 || numberOfColumn == COLUMN_3 || numberOfColumn == COLUMN_6)
			this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());

		else
			// сортируем
			this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumn, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
}
