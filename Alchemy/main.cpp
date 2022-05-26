#include <iostream>
#include "AlchemyProgram.h"
#include "FileReader.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    Alchemist alchemist;

    AlchemicalUserInterface userInterface;

    userInterface.setTitle("Зельеварение");

    userInterface.launchMainLoop();
}

