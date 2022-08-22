#include "SellingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingIngredientsMenuState::SellingIngredientsMenuState()
{
}

SellingIngredientsMenuState::SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Продажа ингредиентов";
	this->goToTitle = "Продать ингредиенты";
	this->numberOfStates = 1;
}

//SellingIngredientsMenuState::~SellingIngredientsMenuState()
//{
//	clear();
//}

void SellingIngredientsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (SellingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// Текст ошибки в случае неудачной продажи
	string error = "";

	string choiceIngredient = "Введите № ингредиента: ";

	string choiceNumberOfIngredient = "Введите кол-во ингредиента: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (true)
	{
		// если кол-во доступных ингредиентов меньше ОДНОГО, то продать ничего не выйдет
		if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
		{
			error = "У вас совсем нет ингредиентов.\nПрикупите чего-нибудь у Аркадии.\nESC - назад";

			printMenuTitle();

			printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

			this->alchemicalUserInterface->chooseExit();

			exitMenu();

			return;
		}

		printMenu(choiceIngredient, choiceNumberOfIngredient);

		// начальная страница таблицы
		int page = FIRST_PAGE;

		// печатаем таблицу имеющихся ингредиентов
		this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// если был нажат esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			exitMenu();

			return;
		}

		int ingredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);

		int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, Y_COORD_AFTER_MENU_TITLE_3);

		// если ввели отсутствующие id
		checkIngredientsId(ingredientId);

		checkNumberOfIngredient(numberOfIngredient, ingredientId);

		alchemyLogic->sellIngredient(ingredientId, numberOfIngredient);

		string congratulations = "Вы отличный торговец!";

		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		// ждем нажатия любой клавиши
		char a = _getch();

		break;
	}
}

MenuState* SellingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void SellingIngredientsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&SellingIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* SellingIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void SellingIngredientsMenuState::printMenu(string choiceIngredient, string choiceNumberOfIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceNumberOfIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
}

void SellingIngredientsMenuState::checkIngredientsId(int& ingredientId)
{
	int index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);

	while (index == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(ingredientId, Y_COORD_AFTER_MENU_TITLE_2);

		index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);
	}
}

void SellingIngredientsMenuState::checkNumberOfIngredient(int& numberOfIngredient, int ingrdientId)
{
	int currentNumber = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(ingrdientId)->getNumber();

	while (numberOfIngredient > currentNumber)
	{
		string textOfError = "У вас нет такого количества ингредиента с номером " + to_string(ingrdientId) + ", введите меньшее количество: ";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD, textOfError);

		numberOfIngredient = this->alchemicalUserInterface->chooseNumber(textOfError, Y_COORD_AFTER_MENU_TITLE_3);
	}
}