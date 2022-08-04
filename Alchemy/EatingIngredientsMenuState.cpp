#include "EatingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

EatingIngredientsMenuState::EatingIngredientsMenuState()
{
}

EatingIngredientsMenuState::EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Съешь ингредиент";
	this->goToTitle = "Съесть ингредиент";
	this->numberOfStates = 1;
}

//EatingIngredientsMenuState::~EatingIngredientsMenuState()
//{
//	clear();
//}

void EatingIngredientsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (EatingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// Текст ошибки в случае неудачной продажи
	string error = "";

	string choiceIngredient = "Введите № ингредиента: ";/*

	string choiceNumberOfIngredient = "Введите кол-во ингредиента: ";*/

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (true)
	{
		// если кол-во доступных ингредиентов меньше ОДНОГО, то съесть ничего не выйдет
		if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
		{
			error = "У вас совсем нет ингредиентов.\nПрикупите чего-нибудь у Аркадии.\nESC - назад";

			printMenuTitle();

			printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

			this->alchemicalUserInterface->chooseExit();

			exitMenu();

			return;
		}

		printMenuTitle();

		printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

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

		int ingredientId = printChoiceIngredientId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		// если ввели отсутствующие id
		checkIngredientsId(ingredientId);

		alchemyLogic->eatIngredient(ingredientId);

		string congratulations = "Вы съели ингредиент и узнали его эффект!";

		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		// ждем нажатия любой клавиши
		char a = _getch();

		break;
	}
}

MenuState* EatingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void EatingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void EatingIngredientsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&EatingIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* EatingIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void EatingIngredientsMenuState::checkIngredientsId(int& ingredientId)
{
	int index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);

	bool wasClosedEff = wasClosedEffect(ingredientId);

	while (index == NO_POSITION || wasClosedEff == false)
	{
		string error;

		if (index == NO_POSITION)

			error = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";

		else
			error = "У ингредиента с номером " + to_string(ingredientId) + " все эффекты открыты, выберите другой номер: ";

		// сбрасываем
		wasClosedEff = false;

		printErrorAndMakeChoiceAgain(Y_COORD_AFTER_MENU_TITLE_2, error, ingredientId);

		index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);

		wasClosedEff = wasClosedEffect(ingredientId);
	}
}

//void EatingIngredientsMenuState::printErrorWrongIdAndMakeChoiceAgain(string int& ingredientId, int yCoord)
//{
//	string textOfError = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";
//
//	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
//}

void EatingIngredientsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceIngredientId(yCoord, textOfError.size() + 1);
}

bool EatingIngredientsMenuState::wasClosedEffect(int ingredientId)
{
	bool wasClosedEffect = false;

	Ingredient* ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(ingredientId);

	// Итератор на начало
	auto beginIter = ingredient->getBeginIteratorOfEffectsId();

	// Итератор на конец
	auto endIter = ingredient->getEndIteratorOfEffectsId();

	for (auto i = beginIter; i != endIter; ++i)
	{
		if (i->second == UNKNOWN)
		{
			wasClosedEffect = true;

			break;
		}
	}

	return wasClosedEffect;
}

//void EatingIngredientsMenuState::printErrorWrongEffectAndMakeChoiceAgain(int& ingredientId, int yCoord)
//{
//}
