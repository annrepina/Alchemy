#include <iostream>
#include "AlchemyProgram.h"
#include "FileReader.h"
#include <ctime>

using namespace std;


#include "EffectsTableBuilder.h"
#include "AlchemicalUserInterface.h"
#include "IngredientsTableBuilder.h"
//#include <consoleapi2.h>

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    srand(1);

    //AlchemicalUserInterface userInterface;

    //userInterface.setTitle("Зельеварение");

    //userInterface.launchMainLoop();




    AlchemyProgramParser parser;

    EffectsTableBuilder* effectsTableBuilder = new EffectsTableBuilder();

    effectsTableBuilder->buildTable(&parser);

    EffectsTable* table = effectsTableBuilder->getResult();

    table->print();

    delete effectsTableBuilder;
    delete table;

    // 

    //IngredientBuilder* ingredientBuilder = new IngredientBuilder();

    //ingredientBuilder->setEffectsTable(table);

    //ingredientBuilder->fillEffectId();

    //IngredientsTableBuilder* ingredientsTableBuilder = new IngredientsTableBuilder();

    //ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

    //ingredientsTableBuilder->buildIngredientsTable(&parser);

    //IngredientsTable* ingredientsTable = ingredientsTableBuilder->getResult();


    //ingredientsTable->print();


    
}

