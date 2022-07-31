#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Создание зелий";
    this->goToTitle = "Создать зелье";
    this->numberOfStates = 0;
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

	string choiceFirstIngredient = "Введите № первого ингредиента: ";

	string choiceSecondIngredient = "Введите № второго ингредиента: ";

	// Получаем нашу логику
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// Получаем таблицу ингредиентов 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (false == success)
	{
		printMenu(error, choiceFirstIngredient, choiceSecondIngredient);

		// начальная страница таблицы
		int page = FIRST_PAGE;

		// печатаем таблицу имеющихся ингредиентов
		this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// если был нажат esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			this->alchemicalUserInterface->setState(this->getNextState());

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

		// Имя зелья
		string name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

		int price = potion->getPrice();

		int power = potion->getPower();

		success = this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

		// Если зелье не получилось
		if (!success)
		{
			error = "К сожалению, зелье не получилось!";
		}
		else
		{
			cout << "Вы создали зелье - " << name << ". Цена - " << price << " септ." << " Мощность - " << power << ".";

			break;
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

void CreatingPotionsMenuState::printMenu(string error, string choiceFirstIngredient, string choiceSecondIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

int CreatingPotionsMenuState::printChoiceId(int yCoord, int xCoord)
{
	// Переходим по координате для ввода первого id
	cout << goToXY(yCoord, xCoord);

	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

	return ingredientId;
}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId)
{
	// Получаем нашу таблицу
	IngredientsTable* ingredientTable = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable();

	// уменьшаем кол-во ингредиентов
	ingredientTable->decreaseNumberOfIngredient(firstIgredientId);

	ingredientTable->decreaseNumberOfIngredient(secondIngredientId);
}

void CreatingPotionsMenuState::checkIngredientsId(int firstIngredientId, int& secondIngredientId)
{
	// если ввели одинаковые ингредиенты
	while (firstIngredientId == secondIngredientId)
	{
		string textOfError = "Вы уже выбрали ингредиент с номером " + to_string(secondIngredientId) + "выберите другой номер снова: ";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, 1, textOfError);

		secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, textOfError.size() + 1);
	}
}
