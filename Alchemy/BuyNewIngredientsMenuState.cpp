#include "BuyNewIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState()
{
}

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "Покупка ингредиентов, которых нет в \"Котелке Аркадии\"";
    this->goToTitle = "Купить ингредиенты, которых нет в \"Котелке Аркадии\"";
    this->numberOfStates = 1;
}

void BuyNewIngredientsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	// Текст ошибки в случае неудачной покупки
	string error = "";

	// Удачно ли купили ингредиент (хватило ли денег)
	bool success = false;

	// такого ингредиента еще нет?
	bool tryAddNewIngredient = false;

	//// Задаем таблицу эффектов
	//builder.setEffectsTable(this->alchemicalUserInterface->getAlchemyLogic()->getEffectsTable());

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyNewIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	while (false == success)
	{
		string ingredientName;

		// id ингредиента
		int ingredientId;

		Ingredient* ingredient;

		printMenuTitle();

		string inputName = "Введите название ингредиента: ";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		//cout << inputName;

		//cin.getline()

		//std::string name;
		//std::cout << "Input name: ";
		std::cin.ignore(1, '\n');
		getline(std::cin, ingredientName);

		//ingredientName = std::getline(std::cin, ingredientName);

		//cin.getline(ingredientName, 25, '\n');

		//getline(cin, ingredientName, '\n');

		//cin >> ingredientName;

		// Удачно ли добавили новый ингредиент
		tryAddNewIngredient = this->alchemicalUserInterface->getAlchemyLogic()->tryAddNewIngredientToTable(ingredientName);

		// если неудачно, значит такой ингредиент в базе уже есть
		if (!tryAddNewIngredient)
		{
			cout << "У Аркадии есть " << ingredientName << ". ";

			// ищем по имени этот ингредиент
			ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientByName(ingredientName);

			// выводим скок стоит
			//cout << ingredientName << " стоит " << ingredient->getPrice() << " септ." << endl;

			// узнаем id ингредиента
			ingredientId = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIdByIngredient(ingredient);
		}
		else
		{
			ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getEndIterator()->second;

			ingredientId = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getEndIterator()->first;
		}

		// выводим скок стоит
		cout << "Цена - " << ingredient->getPrice() << " септ." << endl;

		string choiceNumber = "Введите кол-во: ";

		cout << choiceNumber;

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_4);

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(ingredientId, number);

		// Если покупка не состоялась
		if (!success)
		{
			error = "Недостаточно монет, попробуйте снова:";
			continue;
		}

		cout << "Ингредиент куплен!" << endl;
	}

	cout << "Enter - продолжить покупки, ESC - назад";

	chooseContinueOrGoBack();

	// если был нажат ESC, то выходим назад
	if (this->alchemicalUserInterface->getExitFlag() == true)
	{
		// сбрасываем флаг
		this->alchemicalUserInterface->setExitFlag(false);

		this->alchemicalUserInterface->setState(this->getNextState());
	}
}

MenuState* BuyNewIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void BuyNewIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyNewIngredientsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&BuyNewIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* BuyNewIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
