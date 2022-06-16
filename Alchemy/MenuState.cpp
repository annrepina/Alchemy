#include "MenuState.h"
#include "AlchemicalUserInterface.h"

MenuState::MenuState()
{
	this->title = "";
	this->alchemicalUserInterface = nullptr;
}

MenuState::MenuState(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

MenuState::~MenuState()
{
}

void MenuState::setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

void MenuState::printMenu()
{

}

void MenuState::printMenuTitle()
{
	//eraseScreenAfterAlchemist();

	//this->alchemicalUserInterface->

	this->alchemicalUserInterface->currentXCursorCoord = calculateXCoordInMiddle(title);

	//this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(this->alchemicalUserInterface->currentYCursorCoord - TWO_LINES, this->alchemicalUserInterface->currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}
