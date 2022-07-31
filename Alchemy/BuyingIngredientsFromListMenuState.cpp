#include "BuyingIngredientsFromListMenuState.h"
#include "BuyingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState()
{
	//index = 0;
}

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Покупка ингредиентов из \"Котелка Аркадии\"";
	this->goToTitle = "Купить ингредиенты из \"Котелка Аркадии\"";
	this->numberOfStates = 1;
	//this->index = 0;
}

//BuyingIngredientsFromListMenuState::~BuyingIngredientsFromListMenuState()
//{
//}

void BuyingIngredientsFromListMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	// Успешность покупки 
	bool success = false;

	// Текст ошибки в случае неудачной покупки
	string error = "";

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyingIngredientsFromListMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	while (false == success)
	{
		// начальная страница таблицы
		int page = FIRST_PAGE;

		string choiceIngredient = "Введите № ингредиента: ";

		string choiceNumber = "Введите кол-во ингредиентов: ";

		// Флаг ддля выхода из цикла
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

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

		// перейти по координате для выбора
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		int id = this->alchemicalUserInterface->chooseId(/*choiceIngredient, */AlchemicalUserInterface::TableCode::IngredientTable);

		//if (wasExit(id))
		//	return;

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);

		//if (wasExit(number))
		//	return;

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(id, number);

		// Если покупка не состоялась
		if (!success)
		{
			error = "Недостаточно монет, попробуйте снова:";
		}
	}
}

MenuState* BuyingIngredientsFromListMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void BuyingIngredientsFromListMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyingIngredientsFromListMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&BuyingIngredientsFromListMenuState::createReturnMenuState);
	}
}

ReturnMenuState* BuyingIngredientsFromListMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

