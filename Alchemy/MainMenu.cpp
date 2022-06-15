#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface) 
{
	this->title = "Главное меню";
}

void MainMenu::printMenu()
{

}
