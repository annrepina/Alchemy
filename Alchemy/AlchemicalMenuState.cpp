#include "AlchemicalMenuState.h"

AlchemicalMenuState::AlchemicalMenuState()
{
}

AlchemicalMenuState::AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "���� �������";
	this->goToTitle = "����������";
}

AlchemicalMenuState::~AlchemicalMenuState()
{
	clear();
}

void AlchemicalMenuState::setListOfStates()
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
