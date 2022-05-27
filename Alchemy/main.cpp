#include <iostream>
#include "AlchemyProgram.h"
#include "FileReader.h"

using namespace std;


#include "EffectsTableBuilder.h"
#include "AlchemicalUserInterface.h"
//#include <consoleapi2.h>

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    //Alchemist alchemist;

    //AlchemicalUserInterface userInterface;

    //userInterface.setTitle("Зельеварение");

    //userInterface.launchMainLoop();

    AlchemyProgramParser parser;

    EffectsTableBuilder effectsTableBuilder;

    effectsTableBuilder.buildEffectstable(&parser);

    EffectsTable* table = effectsTableBuilder.getResult();

    table->print();


}

