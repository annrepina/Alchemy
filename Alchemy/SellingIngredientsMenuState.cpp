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

	//// Успешность продажи 
	//bool success = false;

	// Текст ошибки в случае неудачной продажи
	string error = "";

	string choiceIngredient = "Введите № ингредиента: ";

	string choiceNumberOfIngredient = "Введите кол-во ингредиента: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (/*false == success*/true)
	{
		// если кол-во доступных ингредиентов меньше ОДНОГО, то продать ничего не выйдет
		if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
		{
			error = "Для продажи ингредиентов у вас недостаточно ингредиентов.\nПрикупите чего-нибудь у Аркадии.\nESC - назад";

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

		int ingredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);

		// если ввели отсутствующие id
		checkIngredientsId(ingredientId);

		checkNumberOfIngredient(numberOfIngredient, ingredientId);

		//// уменьшаем кол-во выбранных ингредиентов
		//decreaseNumberOfIngredients(ingredientId);

		alchemyLogic->sellIngredient(ingredientId, numberOfIngredient);

		//// первый ингредиент
		//Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(ingredientId);

		//// второй ингредиент
		//Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);


		//Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		//string name = "";
		//int price = 0;
		//int power = 0;

		//// ЕСЛИ ЗЕЛЬЕ НЕ ИСПОРЧЕНО
		//if (potion->getEffectId() > 0)
		//{
		//	// Имя зелья
		//	name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

		//	price = potion->getPrice();

		//	power = potion->getPower();

		//	// уведомляем подписчиков об изменение видимости открытых эффектов
		//	firstIngredient->notify(ingredientId);
		//	secondIngredient->notify(secondIngredientId);
		//}

		//success = this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

		//// Если зелье не получилось
		//if (!success)
		//{
		//	error = "К сожалению, зелье не получилось!";

		//	printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		//	error = "";
		//}
		//else
		//{
			string congratulations = "Вы отличный торговец!";

		//	//cout << "" << name << ". Цена - " << price << " септ." << " Мощность - " << power << ".";
			cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

			printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

			// ждем нажатия любой клавиши
			char a = _getch();

			break;
		//}
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

int SellingIngredientsMenuState::printChoiceId(int yCoord, int xCoord)
{
	// Переходим по координате для ввода первого id
	cout << goToXY(yCoord, xCoord);

	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

	return ingredientId;
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1);
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

		numberOfIngredient = this->alchemicalUserInterface->chooseNumber(textOfError, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);
	}
}

//void SellingIngredientsMenuState::decreaseNumberOfIngredients(int igredientId)
//{
//	// Получаем нашу таблицу
//	IngredientsTable* ingredientTable = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable();
//
//	// уменьшаем кол-во ингредиентов
//	ingredientTable->decreaseNumberOfIngredient(igredientId);
//}





