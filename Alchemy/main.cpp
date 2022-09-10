#include <iostream>
#include "AlchemyLogic.h"
#include "FileReader.h"
#include <ctime>

using namespace std;


#include "EffectsTableBuilder.h"
#include "AlchemicalUserInterface.h"
#include "IngredientsTableBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"
//#include <consoleapi2.h>

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    //SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //MainMenuState* state = new MainMenuState();

    //srand(1);

    //string path = "AlchemyLogicBinary.txt";

    AlchemicalUserInterface userInterface;

    //userInterface.setTitle("Зельеварение");

    userInterface.launchProgram();




    //AlchemyProgramParser parser;

    //EffectsTableBuilder* effectsTableBuilder = new EffectsTableBuilder();

    //effectsTableBuilder->buildTable(&parser);

    //EffectsTable* table = effectsTableBuilder->getResult();

    //table->print();

    //delete effectsTableBuilder;
    //delete table;

     

    //IngredientBuilder* ingredientBuilder = new IngredientBuilder();

    //ingredientBuilder->setEffectsTable(table);

    //ingredientBuilder->fillEffectId();

    //IngredientsTableBuilder* ingredientsTableBuilder = new IngredientsTableBuilder();

    //ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

    //ingredientsTableBuilder->buildTable(&parser);

    //IngredientsTable* ingredientsTable = ingredientsTableBuilder->getResult();



    //ingredientsTable->calculateLength();
    //ingredientsTable->calculateXCoordForPrinting();

    //ingredientsTable->print();




    //IngredientsTablePrinter printer;

    //IngredientsTable* table = new IngredientsTable();

    //printer.print(table);

    //calculateConsoleWidth();

    //MainMenuState* mainMenu = new MainMenuState(&userInterface);
    //mainMenu->printMenu();
    //delete mainMenu;
}

