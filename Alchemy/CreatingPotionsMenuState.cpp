#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

#define DEBUG

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Создание зелий";
    this->goToTitle = "Создать зелье";
    this->numberOfStates = 1;
}

//CreatingPotionsMenuState::~CreatingPotionsMenuState()
//{
//    clear();
//}

void CreatingPotionsMenuState::printMenu()
{
    // Сбрасываем координату каждый раз заходя в метод печати
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (CreatingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

    // Успешность покупки 
    bool success = false;

    // Текст ошибки в случае неудачной покупки
    string error = "";

	// если кол-во доступных ингредиентов меньше двух, то алхимичить не выйдет
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING)
	{
		error = "Для создания зелий у вас недостаточно ингредиентов.\nПрикупите чего-нибудь у Аркадии.\nESC - назад";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	string choiceFirstIngredient = "Введите № первого ингредиента: ";

	string choiceSecondIngredient = "Введите № второго ингредиента: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу зелий 
	PotionTable* potionsTable = alchemyLogic->getPotionTable();

	while (false == success)
	{
		printMenu(choiceFirstIngredient, choiceSecondIngredient);

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

		int firstIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1);

		int secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, choiceSecondIngredient.size() + 1);

		// если ввели одинаковые ингредиенты
		checkIngredientsId(firstIngredientId, secondIngredientId);

		// уменьшаем кол-во выбранных ингредиентов
		decreaseNumberOfIngredients(firstIngredientId, secondIngredientId);

		// первый ингредиент
		Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(firstIngredientId);

		// второй ингредиент
		Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);

		Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		string name = "";
		int price = 0;
		int power = 0;

		// ЕСЛИ ЗЕЛЬЕ НЕ ИСПОРЧЕНО
		if (potion->getEffectId() > 0)
		{
			// Имя зелья
			name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

			price = potion->getPrice();

			power = potion->getPower();

			// проверка зелья, есть ли такое уже
			this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

			// уведомляем подписчиков об изменение видимости открытых эффектов
			firstIngredient->notify(firstIngredientId, NOT_NEW_ELMENT);
			secondIngredient->notify(secondIngredientId, NOT_NEW_ELMENT);

			string congratulations = "Вы создали зелье - " + name + ". Цена - " + to_string(price) + " септ. Мощность - " + to_string(power) + ".";

			printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

			// ждем нажатия любой клавиши
			char a = _getch();

			break;
		}

		// Если зелье не получилось
		else
		{
			error = "К сожалению, зелье не получилось!";

			printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

			error = "";
		}
	}
}

MenuState* CreatingPotionsMenuState::getNextState()
{
    return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void CreatingPotionsMenuState::setListOfStates()
{
    this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void CreatingPotionsMenuState::setListOfCreatingFunctions()
{
    // если вектор пустой
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&CreatingPotionsMenuState::createReturnMenuState);
    }
}

ReturnMenuState* CreatingPotionsMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void CreatingPotionsMenuState::printMenu(string choiceFirstIngredient, string choiceSecondIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

//int CreatingPotionsMenuState::printChoiceId(int yCoord, int xCoord)
//{
//	// Переходим по координате для ввода первого id
//	cout << goToXY(yCoord, xCoord);
//
//	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);
//
//	return ingredientId;
//}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId)
{
	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// уменьшаем кол-во ингредиентов
	alchemyLogic->decreaseNumberOfIngredient(firstIgredientId, 1);

	alchemyLogic->decreaseNumberOfIngredient(secondIngredientId, 1);
}

void CreatingPotionsMenuState::checkIngredientsId(int& firstIngredientId, int& secondIngredientId)
{
	int firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(firstIngredientId);
	int secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(secondIngredientId);

	while (firstIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(firstIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		checkIdForEquality(firstIngredientId, secondIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(firstIngredientId);
	}

	while (secondIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(secondIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		checkIdForEquality(secondIngredientId, firstIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(secondIngredientId);
	}
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1);
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void CreatingPotionsMenuState::checkIdForEquality(int& firstIngredientId, int secondIngredientId, int YCoord)
{
	// если ввели одинаковые ингредиенты
	while (firstIngredientId == secondIngredientId)
	{
		string textOfError = "Вы уже выбрали ингредиент с номером " + to_string(firstIngredientId) + ", выберите другой номер: ";

		printErrorAndMakeChoiceAgain(YCoord, textOfError, firstIngredientId);
	}
}

//void CreatingPotionsMenuState::exitMenu()
//{
//	// сбрасываем флаг
//	this->alchemicalUserInterface->setExitFlag(false);
//
//	this->alchemicalUserInterface->setState(this->getNextState());
//}
