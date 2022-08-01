#include "SellingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingIngredientsMenuState::SellingIngredientsMenuState()
{
}

SellingIngredientsMenuState::SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Продажа ингредиентов";
	this->goToTitle = "Продать ингредиенты";
	this->numberOfStates = 0;
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

	// Успешность продажи 
	bool success = false;

	// Текст ошибки в случае неудачной продажи
	string error = "";

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

	string choiceIngredient = "Введите № ингредиента: ";

	string choiceNumberOfIngredient = "Введите кол-во ингредиента: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (false == success)
	{
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

		//// если ввели одинаковые ингредиенты
		//checkIngredientsId(ingredientId, secondIngredientId);

		//// уменьшаем кол-во выбранных ингредиентов
		//decreaseNumberOfIngredients(ingredientId, secondIngredientId);

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
		//	string congratulations = "Вы создали зелье - " + name + ". Цена - " + to_string(price) + " септ. Мощность - " + to_string(power) + ".";

		//	//cout << "" << name << ". Цена - " << price << " септ." << " Мощность - " << power << ".";

		//	printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		//	// ждем нажатия любой клавиши
		//	char a = _getch();

		//	break;
		//}
	}


}

MenuState* SellingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new SellingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
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
	return new ReturnMenuState(new SellingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
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



