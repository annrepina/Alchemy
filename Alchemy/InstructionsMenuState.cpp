#include "InstructionsMenuState.h"
#include "MainMenuState.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Наставления начинающему алхимику";
	this->goToTitle = "Читать наставления начинающему алхимику";
	this->numberOfStates = NUMBER_OF_INSTRUCIONS_MENU_ITEMS;
}

//InstructionsMenuState::~InstructionsMenuState()
//{ 
//	clear();
//}

void InstructionsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (InstructionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	cout << "Ознакомьтесь с инструкцией к программе";

	MenuState::printMenu();
}

MenuState* InstructionsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void InstructionsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void InstructionsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&InstructionsMenuState::createReturnMenuState);
	}
}

//void InstructionsMenuState::fillStateCreatingFunctions()
//{
//	// Стартовый ключ в ассоциативном массиве
//	int startKey = this->currentYCursorCoordState;
//
//	// Заполняем ассоциативный массив
//	for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
//	{
//		stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
//	}
//}

ReturnMenuState* InstructionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
