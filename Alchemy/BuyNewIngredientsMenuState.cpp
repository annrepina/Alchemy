#include "BuyNewIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState()
{
}

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Покупка ингредиентов, которых нет в \"Котелке Аркадии\"";
    this->goToTitle = "Купить ингредиенты, которых нет в \"Котелке Аркадии\"";
    this->numberOfStates = 0;
}

void BuyNewIngredientsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	string ingredientName = "";

	// Текст ошибки в случае неудачной покупки
	string error = "";

	// Удачно ли купили ингредиент
	bool success = false;

	//// Задаем таблицу эффектов
	//builder.setEffectsTable(this->alchemicalUserInterface->getAlchemyLogic()->getEffectsTable());

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyNewIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	while (false == success)
	{
		string inputName = "Введите название ингредиента: ";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		//cout << inputName;

		cin >> ingredientName;

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryAddNewIngredientToTable(ingredientName);

		if (!success)
		{
			error = "Ингредиент с именем \"" + ingredientName + "\" уже существует, попробуйте снова:";
		}

		cout << "Успешно куплен по ц";
	}




	



		string choiceNumber = "Введите кол-во ингредиентов: ";

		// Флаг ддля выхода из цикла
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// если был нажат esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			this->alchemicalUserInterface->setState(this->getNextState());

			return;
		}

		int id = this->alchemicalUserInterface->chooseId(inputName, AlchemicalUserInterface::TableCode::IngredientTable);

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable);

		success = this->alchemicalUserInterface->tryAddIngredientFromList(id, number);

		// Если покупка не состоялась
		if (!success)
		{
			error = "Недостаточно монет, попробуйте снова:";
		}
	//}
}

MenuState* BuyNewIngredientsMenuState::getNextState()
{
    return nullptr;
}

void BuyNewIngredientsMenuState::setListOfStates()
{
}

void BuyNewIngredientsMenuState::setListOfCreatingFunctions()
{
}
