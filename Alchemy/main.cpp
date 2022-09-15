#include <iostream>
#include "AlchemyLogic.h"
#include <ctime>
#include "EffectsTableBuilder.h"
#include "AlchemicalUserInterface.h"
#include "IngredientsTableBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AlchemicalUserInterface* userInterface = new AlchemicalUserInterface();

    userInterface->launchProgram();

    delete userInterface;
}