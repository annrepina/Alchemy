#include "SellingPotionsMenuState.h"

SellingPotionsMenuState::SellingPotionsMenuState()
{
}

SellingPotionsMenuState::SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "���� ������� ������������";
	this->goToTitle = "������� �����������";
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

void SellingPotionsMenuState::fillStateCreatingFunctions()
{
}
