#include "AlchemicalMenuState.h"

AlchemicalMenuState::AlchemicalMenuState()
{
}

AlchemicalMenuState::AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Меню алхимии";
	this->goToTitle = "Алхимичить";
	this->numberOfStates = NUMBER_OF_ALCHEMICAL_MENU_ITEMS;
}

AlchemicalMenuState::~AlchemicalMenuState()
{
	clear();
}

void AlchemicalMenuState::setListOfStates()
{

}

void AlchemicalMenuState::setListOfCreatingFunctions()
{
}

MenuState* AlchemicalMenuState::getNextState()
{
	return nullptr;
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
