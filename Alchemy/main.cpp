#include <iostream>
#include "AlchemyProgram.h"
#include "FileReader.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);

    //AlchemyProgram program;

    //program.launchMainLoop();

    Alchemist alchemist;

    UserInterface userInterface;

    userInterface.setTitle("Зельеварение");

    userInterface.setAlchemist(&alchemist);

    userInterface.launchMainLoop();




    //auto path = "D:\\Hello.txt";

    //FileReader reader(path);

    //string res = reader.read();

    //cout << res << endl;
}

