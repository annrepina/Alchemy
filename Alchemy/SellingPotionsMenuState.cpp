#include "SellingPotionsMenuState.h"

SellingPotionsMenuState::SellingPotionsMenuState()
{
}

SellingPotionsMenuState::SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Продажа зелий";
	this->goToTitle = "Продать зелья";
	this->numberOfStates = 0;
}

//SellingPotionsMenuState::~SellingPotionsMenuState()
//{
//	clear();
//}

void SellingPotionsMenuState::printMenu()
{
}

MenuState* SellingPotionsMenuState::getNextState()
{
	return nullptr;
}

void SellingPotionsMenuState::setListOfStates()
{
}

void SellingPotionsMenuState::setListOfCreatingFunctions()
{
}
