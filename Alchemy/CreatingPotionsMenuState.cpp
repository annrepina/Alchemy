#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Создание зелий";
    this->goToTitle = "Создать зелье";
    this->numberOfStates = 1;
}

void CreatingPotionsMenuState::printMenu()
{
    // Сбрасываем координату каждый раз заходя в метод печати
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (CreatingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

    // Текст ошибки в случае неудачной покупки
    string error = "";

	// если кол-во доступных ингредиентов меньше двух, то алхимичить не выйдет
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING)
	{
		error = "Для создания зелий у вас недостаточно ингредиентов.\nПрикупите чего-нибудь у Аркадии.\nESC - назад";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	string choiceFirstIngredient = "Введите № первого ингредиента: ";
	string choiceSecondIngredient = "Введите № второго ингредиента: ";
	string choiceNumberOfPoition = "Введите сколько хотите создать зелья: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу зелий 
	PotionTable* potionsTable = alchemyLogic->getPotionTable();

	printMenu(choiceFirstIngredient, choiceSecondIngredient, choiceNumberOfPoition);

	// начальная страница таблицы
	int page = FIRST_PAGE;

	// печатаем таблицу имеющихся ингредиентов
	this->alchemicalUserInterface->printIngredientsTableWithAvailableToUserElements(page);

	// если был нажат esc
	if (true == this->alchemicalUserInterface->getWasExit())
	{
		goBack();

		return;
	}

	int firstIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
	int secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, choiceSecondIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);

	int numberOfPotion = printChoiceNumber(Y_COORD_AFTER_MENU_TITLE_4, choiceNumberOfPoition);

	// если ввели одинаковые ингредиенты
	checkIngredientsId(firstIngredientId, secondIngredientId);

	checkNumberOfIngredients(firstIngredientId, secondIngredientId, numberOfPotion);

	// уменьшаем кол-во выбранных ингредиентов
	decreaseNumberOfIngredients(firstIngredientId, secondIngredientId, numberOfPotion);

	// первый ингредиент
	Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(firstIngredientId);

	// второй ингредиент
	Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);

	// Создаем вектор созданных зелий
	vector<Potion*> potions;

	// добавляем созданные зелья в вектор
	for (int i = 0; i < numberOfPotion; ++i)
	{
		Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		potions.push_back(potion);
	}

	string name = "";
	int price = 0;
	int power = 0;

	// Если первое зелье не испорчено, то и все нормальные
	if (potions[0]->getEffectId() > 0)
	{
		// изначальный размер таблицы
		int originalSizeOfPoitionTable = potionsTable->getSize();

		// Создаем вектор,куда мы поместим только уникальные зелья
		vector<Potion*> uniquePotions;

		for (int i = 0; i < numberOfPotion; ++i)
		{
			// проверка зелья, есть ли такое уже
			alchemyLogic->checkPotion(potions[i], uniquePotions);
		}

		// размер ьаблицы после добавления зелий
		int sizeOfPotionTableAfterAdding = potionsTable->getSize();

		// кол-во добавленных зелий
		int numberOfAddedPotions = sizeOfPotionTableAfterAdding - originalSizeOfPoitionTable;

		// уведомляем подписчиков об изменение видимости открытых эффектов
		firstIngredient->notify(firstIngredientId, NOT_NEW_ELEMENT);
		secondIngredient->notify(secondIngredientId, NOT_NEW_ELEMENT);

		int vecSize = uniquePotions.size();

		for (int i = 0; i < vecSize; ++i)
		{
			// Имя зелья
			name = alchemyLogic->getEffectsTable()->getEffectByKey(uniquePotions[i]->getEffectId())->getName();

			price = uniquePotions[i]->getPrice();

			power = uniquePotions[i]->getPower();

			string congratulations = "Вы создали зелья - " + name + ". Цена - " + to_string(price) + " септ. Мощность - " + to_string(power) + ".";

			printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

			cout << endl;
		}
	}

	// Если зелье не получилось
	else
	{
		error = "К сожалению, зелье не получилось!";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_5, STANDARD_CURSOR_X_COORD, error);
	}

	// ждем нажатия любой клавиши
	char a = _getch();
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

void CreatingPotionsMenuState::printMenu(string choiceFirstIngredient, string choiceSecondIngredient, string choiceNumberOfIngredients)
{
	printMenuTitle();

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);
	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
	printColoredTextByCoords(choiceNumberOfIngredients, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);
}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId, int number)
{
	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// уменьшаем кол-во ингредиентов
	alchemyLogic->decreaseNumberOfIngredient(firstIgredientId, number);
	alchemyLogic->decreaseNumberOfIngredient(secondIngredientId, number);
}

void CreatingPotionsMenuState::checkIngredientsId(int& firstIngredientId, int& secondIngredientId)
{
	int firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(firstIngredientId);
	int secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(secondIngredientId);

	while (firstIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(firstIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		checkIdForEquality(firstIngredientId, secondIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(firstIngredientId);
	}

	while (secondIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(secondIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		checkIdForEquality(secondIngredientId, firstIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(secondIngredientId);
	}
}

void CreatingPotionsMenuState::checkNumberOfIngredients(int firstIngredientId, int secondIngredientId, int &numberOfPotion)
{
	// ингредиенты, полученные по id 
	Ingredient* firstIngredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(firstIngredientId);
	Ingredient* secondIngredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(secondIngredientId);

	int numberOfFirstIngredient = firstIngredient->getNumber();
	int numberOfSecondIngredient = secondIngredient->getNumber();

	int newNumber = numberOfPotion;
	int numberOfIngredient;

	// определяем наименьшее кол-во
	if (numberOfFirstIngredient < numberOfSecondIngredient)
	{
		while (numberOfFirstIngredient < newNumber)
		{
			numberOfIngredient = numberOfFirstIngredient;

			printErrorAboutNumberAndMakeChoiceAgain(firstIngredientId, newNumber, numberOfIngredient, Y_COORD_AFTER_MENU_TITLE_4);

			newNumber = numberOfIngredient;
		}
	}

	else
	{
		while (numberOfSecondIngredient < newNumber)
		{
			numberOfIngredient = numberOfSecondIngredient;

			printErrorAboutNumberAndMakeChoiceAgain(secondIngredientId, newNumber, numberOfIngredient, Y_COORD_AFTER_MENU_TITLE_4);

			newNumber = numberOfIngredient;
		}
	}

	numberOfPotion = newNumber;
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "У вас нет ингредиента с номером " + to_string(ingredientId) + ", выберите другой номер: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void CreatingPotionsMenuState::printErrorAboutNumberAndMakeChoiceAgain(int ingredientId, int previousNumber, int& numberOfIngredients, int yCoord)
{
	string textOfError = "У вас нет такого количества (" + to_string(previousNumber) + ") ингредиента с номером " + to_string(ingredientId) + ", введите меньшее количество : ";

	printErrorAboutNumberAndMakeChoiceAgain(yCoord, textOfError, numberOfIngredients);
}

void CreatingPotionsMenuState::printErrorAboutNumberAndMakeChoiceAgain(int yCoord, string textOfError, int& numberOfIngredients)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	numberOfIngredients = printChoiceNumber(yCoord, textOfError);
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