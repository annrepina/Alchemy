#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"


//string WorkWithIngredientTableMenuState::listOfInnerMenuItems[INNER_MENU_ITEMS] = { "Сортировка", "Поиск" };

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState()
{
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
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

	// начальная страница таблицы
	int page = FIRST_PAGE;

	//// Начальный столбец при сортировке
	//int numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;

	//// Порядок сортировки
	//int orderOfSorting = ASCENDING_ORDER_OF_SORTING;

	printMenuTitle();

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem();

		// сбрасываем флаг после выбора поиск/сортировка
		this->alchemicalUserInterface->setExitFlag(false);

		int operationCode = defineOperation();

		auto tableContent = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTableContent();

		workWithTable((OperationCode)operationCode);

		//this->alchemicalUserInterface->workWithTable((AlchemicalUserInterface::OperationCode)operationCode, AlchemicalUserInterface::TableCode::IngredientTable, tableContent, numberOfColumn, );

	}










	this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::IngredientTable, page);

	this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(DEFAULT_NUMBER_OF_COLUMN, , AlchemicalUserInterface::TableCode::IngredientTable);



	// получаем принтер
	IngredientsTablePrinter* ingredientTablePrinter = this->alchemicalUserInterface->getIngredientsTablePrinter();

	this->alchemicalUserInterface->getAlchemyLogic()->workWithTable((AlchemyLogic::OperationCode)operationCode, ingredientTablePrinter->getTableContent(), DEFAULT_NUMBER_OF_COLUMN, ASCENDING_ORDER_OF_SORTING);
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
	int totalSize = 

	this->initialContent = this->ingredientTablePrinter->getTableContent();

	this->contentAfterSortingAndSearch = this->initialContent;
}

ReturnMenuState* WorkWithIngredientTableMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
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
			while (this->alchemicalUserInterface->getExitFlag() != true)
			{
				// делаем выбор
				this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

				// сортируем
				this->alchemicalUserInterface->getAlchemyLogic()->sortData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


			}



		}
		break;
	}
}
