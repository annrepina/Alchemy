#include "SellingPotionsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingPotionsMenuState::SellingPotionsMenuState()
{
}

SellingPotionsMenuState::SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Продажа зелий";
	this->goToTitle = "Продать зелья";
	this->numberOfStates = 1;
}

//SellingPotionsMenuState::~SellingPotionsMenuState()
//{
//	clear();
//}

void SellingPotionsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (SellingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// Текст ошибки в случае неудачной продажи
	string error = "";

	string choiceIngredient = "Введите № зелья: ";

	string choiceNumberOfIngredient = "Введите кол-во зелья: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	//IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (true)
	{
		// если кол-во доступных зелий меньше ОДНОГО, то продать ничего не выйдет
		if (this->alchemicalUserInterface->getPotionTablePrinter()->getNumberOfLines() < MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING)
		{
			error = "У вас совсем нет зелий.\nСоздайте что-нибудь\.\nESC - назад";

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
		//this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::PotionTable, page);

		// если был нажат esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			exitMenu();

			return;
		}

		//int ingredientId = printChoiceIngredientId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		//int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);

		//// если ввели отсутствующие id
		//checkIngredientsId(ingredientId);

		//checkNumberOfIngredient(numberOfIngredient, ingredientId);

		//alchemyLogic->sellIngredient(ingredientId, numberOfIngredient);

		//string congratulations = "Вы отличный торговец!";

		//cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		//printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		//// ждем нажатия любой клавиши
		//char a = _getch();

		//break;
	}
}

MenuState* SellingPotionsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingPotionsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void SellingPotionsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&SellingPotionsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* SellingPotionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void SellingPotionsMenuState::printMenu(string choicePotion, string choiceNumberOfPotions)
{
	printMenuTitle();

	printColoredTextByCoords(choicePotion, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceNumberOfPotions, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}


