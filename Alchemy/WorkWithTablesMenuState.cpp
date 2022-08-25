#include "WorkWithTablesMenuState.h"
#include "AlchemicalMenuState.h"

WorkWithTablesMenuState::WorkWithTablesMenuState()
{
}

WorkWithTablesMenuState::WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Работа с инвентарем";
	this->goToTitle = "Работать с инвентарем";
	this->numberOfStates = WORK_WITH_TABLES_MENU_ITEMS;
}

//WorkWithTablesMenuState::~WorkWithTablesMenuState()
//{
//	clear();
//}

void WorkWithTablesMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithTablesMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	MenuState::printMenu();
}

MenuState* WorkWithTablesMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void WorkWithTablesMenuState::setListOfStates()
{
	this->listOfStates.push_back(new WorkWithIngredientTableMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new WorkWithPotionTableMenuState(this->alchemicalUserInterface));
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void WorkWithTablesMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&WorkWithTablesMenuState::createWorkWithIngredientTableMenuState);
		this->listOfCreatingFunctions.push_back(&WorkWithTablesMenuState::createWorkWithPotionTableMenuState);
		this->listOfCreatingFunctions.push_back(&WorkWithTablesMenuState::createReturnMenuState);
	}
}

ReturnMenuState* WorkWithTablesMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

WorkWithIngredientTableMenuState* WorkWithTablesMenuState::createWorkWithIngredientTableMenuState()
{
	return new WorkWithIngredientTableMenuState(this->alchemicalUserInterface);
}

WorkWithPotionTableMenuState* WorkWithTablesMenuState::createWorkWithPotionTableMenuState()
{
	return new WorkWithPotionTableMenuState(this->alchemicalUserInterface);
}

