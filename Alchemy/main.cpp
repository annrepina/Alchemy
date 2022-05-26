#include <iostream>
#include "AlchemyProgram.h"
#include "FileReader.h"


#include "EffectsTableBuilder.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    //Alchemist alchemist;

    //AlchemicalUserInterface userInterface;

    //userInterface.setTitle("Зельеварение");

    //userInterface.launchMainLoop();



    EffectsTableBuilder effectsTableBuilder;

    effectsTableBuilder.addEffects(35, POSITIVE);

    effectsTableBuilder.addEffects(20, NEGATIVE);

}

