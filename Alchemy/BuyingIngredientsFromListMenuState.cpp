#include "BuyingIngredientsFromListMenuState.h"
#include "BuyingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState()
{
}

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Покупка ингредиентов из \"Котелка Аркадии\"";
	this->goToTitle = "Купить ингредиенты из \"Котелка Аркадии\"";
	this->numberOfStates = 1;
}

//BuyingIngredientsFromListMenuState::~BuyingIngredientsFromListMenuState()
//{
//}

void BuyingIngredientsFromListMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyingIngredientsFromListMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// начальная страница таблицы
	int page = FIRST_PAGE;

	string choiceIngredient = "Введите № ингредиента: ";

	string choiceNumber = "Введите кол-во ингредиентов: ";

	// Флаг ддля выхода из цикла
	bool exit = false;

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);

	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	//printColoredText(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE + 1, STANDARD_CURSOR_X_COORD);

	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	//printColoredText(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::IngredientTable, page);

	//printTablePagesInLoop(TableCode::IngredientTable, page);

	// если был нажат esc
	if (true == this->alchemicalUserInterface->getExitFlag())
		return;

	int id = this->alchemicalUserInterface->chooseId(choiceIngredient, AlchemicalUserInterface::TableCode::IngredientTable);

	int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable);

	this->alchemicalUserInterface->tryAddIngredientFromList(id, number);
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




	this->listOfCreatingFunctions.push_back(&BuyingIngredientsFromListMenuState::createReturnMenuState);
}

ReturnMenuState* BuyingIngredientsFromListMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

