#include "AlchemicalMenuState.h"

AlchemicalMenuState::AlchemicalMenuState()
{
}

AlchemicalMenuState::AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "���� �������";
	this->goToTitle = "����������";
	this->numberOfStates = NUMBER_OF_ALCHEMICAL_MENU_ITEMS;
}

AlchemicalMenuState::~AlchemicalMenuState()
{
	clear();
}

void AlchemicalMenuState::printMenu()
{
}

void AlchemicalMenuState::setListOfStates()
{
	this->listOfStates.push_back(new CreatingPotionsMenuState(this->alchemicalUserInterface));

}

void AlchemicalMenuState::setListOfCreatingFunctions()
{
}

MenuState* AlchemicalMenuState::getNextState()
{
	return nullptr;
}

void AlchemicalMenuState::fillStateCreatingFunctions()
{
}

//void AlchemicalMenuState::clear()
//{
//	for (auto state : this->menuStates)
//	{
//		delete state.second;
//
//		state.second = nullptr;
//	}
//}
