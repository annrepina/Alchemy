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

	while (false == success)
	{
		// начальная страница таблицы
		int page = FIRST_PAGE;

		string choiceFirstIngredient = "Введите № первого ингредиента: ";

		string choiceSecondIngredient = "Введите № второго ингредиента: ";

		// Флаг ддля выхода из цикла
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

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

		// Переходим по координате для ввода первого id
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1);

		int firstIngredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

		// Переходим по координате для ввода второго id
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_3, choiceFirstIngredient.size() + 1);

		int secondIngredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

		// если ввели одинаковые ингредиенты
		if (firstIngredientId == secondIngredientId)
		{
			string textOfError = "Вы уже выбрали ингредиент с номером " + to_string(secondIngredientId) + "выберите другой номер снова: ";

			this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, 1, textOfError);
		}



		//success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(firstIngredient, number);

		// Если покупка не состоялась
		if (!success)
		{
			error = "Недостаточно монет, попробуйте снова:";
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
