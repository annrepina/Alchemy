#include "Formatting.h"

string goToXY(int yCoord, int xCoord)
{
    string res = "\x1b[" + to_string(yCoord) + ";" + to_string(xCoord) + "H";

    return res;
}

void goToStart()
{
    cout << goToXY(1, 1);
}

string changeTextFormat(string param)
{
    string res = "\x1b[" + param + "m";

    return res;
}

void printNull(int parametr)
{
    if (parametr < 10)
    {
        std::cout << '0';
    }
}

string eraseOnScreen(string param)
{
    string res = "\x1b[" + param + "J";

    return res;
}

string eraseSymbolsOnScreen(string param)
{
    string res = "\x1b[" + param + "X";

    return res;
}

string changeScreenBackground(string r, string g, string b)
{
    // задание зеленого цвета с помощью rgb
    string res = "\x1b]4;00;rgb:" + r + "/" + g + "/" + b + "\x1b\ ";         

    return res;
}

string changeForegroundColorsExtra(string r, string g, string b)
{
    string res = "\x1b[38;2;" + r + ";" + g + ";" + b + "m";        

    return res;
}

string changeBackgroundColorsExtra(string r, string g, string b)
{
    string res = "\x1b[48;2;" + r + ";" + g + ";" + b + "m";

    return res;
}

string changeWindowTitle(string str)
{
    string res = "\x1b]0;" + str + "\x07";

    return res;
}

string resetScreenColorToBlack()
{
    string res = "\x1b]4;00;rgb:" + (string)DEFAULT + "/" + (string)DEFAULT + "/" + (string)DEFAULT + "\x1b\ ";         

    return res;
}

string resetScreenColorToWhite()
{
    string res = "\x1b]4;00;rgb:" + (string)WHITE_DEFAULT_16 + "/" + (string)WHITE_DEFAULT_16 + "/" + (string)WHITE_DEFAULT_16 + "\x1b\ ";

    return res;
}

string resetForegroundColorToBlack()
{
    string res = "\x1b[38;2;" + (string)DEFAULT + ";" + (string)DEFAULT + ";" + (string)DEFAULT + "m";

    return res;
}

string resetExtraBackgroundColorToBlack()
{
    string res = "\x1b[48;2;" + (string)DEFAULT + ";" + (string)DEFAULT + ";" + (string)DEFAULT + "m";

    return res;
}

string resetColorParams()
{
    string res = "\x1b[" + (string)DEFAULT + "m";

    return res;
}

void printFramedText(string text, int yCoord, int xCoord, string param1, string param2)
{
    int stringLength = text.length();          // кол-во символов в строке без нуль терминала

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << turnOnDECMode() << changeTextFormat(param1) << TOP_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << TOP_RIGHT_CORNER << changeTextFormat(param2);

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << changeTextFormat(param1) << VERTICAL_LINE << text << VERTICAL_LINE << changeTextFormat(param2);

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << changeTextFormat(param1) << LOWER_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << LOWER_RIGHT_CORNER << changeTextFormat(param2) << turnOffDECMode();
}

void printFramedText(string text, int yCoord, int xCoord, string r, string g, string b)
{
    int stringLength = text.length();          // кол-во символов в строке без нуль терминала

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << changeBackgroundColorsExtra(r, g, b);
    cout << turnOnDECMode() << TOP_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << TOP_RIGHT_CORNER << resetForegroundColorToBlack();

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << changeBackgroundColorsExtra(r, g, b) << VERTICAL_LINE << text << VERTICAL_LINE << resetForegroundColorToBlack();

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << changeBackgroundColorsExtra(r, g, b) << LOWER_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << LOWER_RIGHT_CORNER << resetForegroundColorToBlack();
    cout << turnOffDECMode();
}

void printFramedText(string text, int yCoord, int xCoord)
{
    int stringLength = text.length();          // кол-во символов в строке без нуль терминала

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << turnOnDECMode() << TOP_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << TOP_RIGHT_CORNER;

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << VERTICAL_LINE;
    
    cout << turnOffDECMode();
    
    cout << text;
    
    cout << turnOnDECMode() << VERTICAL_LINE;

    goToCoordAndIncreaseY(yCoord, xCoord);

    cout << LOWER_LEFT_CORNER;

    for (int i = 0; i < stringLength; ++i)
    {
        cout << HORIZONTAL_LINE;
    }

    cout << LOWER_RIGHT_CORNER;

    cout << turnOffDECMode();
}

void printTextWithBackground(string text, string r, string g, string b)
{
    // Изменяем цвет фона на серый
    cout << changeBackgroundColorsExtra(r, g, b);

    // Печатаем пункт меню
    cout << text;

    // Сбрасываем параметры текста
    cout << resetColorParams();
}

void printColoredText(string text, string r, string g, string b)
{
    cout << changeForegroundColorsExtra(r, g, b);

    cout << text;

    cout << resetColorParams();
}

void goToCoordAndIncreaseY(int& yCoord, int xCoord)
{
    cout << goToXY(yCoord, xCoord);
    ++yCoord;
}

string turnOnDECMode()
{
    // \x1b(0 Включает режим рисования линии DEC
    string res = "\x1b(0";

    return res;
}

string turnOffDECMode()
{
    // \x1b(B Выключает режим рисования линии DEC
    string res = "\x1b(B";

    return res;
}

int calculateConsoleWidth()
{
    // ширина консоли
    int consoleWidth;

    // Извлекает дескриптор для указанного стандартного устройства (стандартный вывод)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);      

    // Структура содержит сведения о буфере экрана консоли
    CONSOLE_SCREEN_BUFFER_INFO consoleSize;

    // Получает информацию об указанном экранном буфере консоли. 
    GetConsoleScreenBufferInfo(hOut, &consoleSize);   

    // получает ширину консоли в байтах 
    consoleWidth = consoleSize.dwSize.X;      

    int consoleLength = consoleSize.dwSize.Y;

    return consoleWidth;
}

int calculateXCoordInMiddle(string text)
{
    int xCoord = (calculateConsoleWidth() / 2) - (text.length() / 2);

    return xCoord;
}

int calculateXCoordInMiddle(int textSize)
{
    int xCoord = (calculateConsoleWidth() / 2) - (textSize / 2);

    return xCoord;
}


void printTopTableFrame(int numberOfColumn, int columWidth)
{
    cout << turnOnDECMode() << TOP_LEFT_CORNER;

    for (int j = 0; j < numberOfColumn; ++j)
    {
        for (int i = 0; i < columWidth; ++i)
        {
            cout << HORIZONTAL_LINE;
        }

        if ((numberOfColumn - 1) != j)
        {
            cout << SYMBOL_T_WORD;
        }
        else
        {
            cout << TOP_RIGHT_CORNER;
        }
    }
}

void printInnerTableFrame(int numberOfColumn, int columWidth)
{
    cout << turnOnDECMode();

    for (int i = 0; i < numberOfColumn; ++i)
    {
        // если это не первый и не последний индекс
        if (FIRST_INDEX != i)
        {
            cout << SYMBOL_CROSS;
        }
        else
        {
            cout << SYMBOL_FIRST_HALF_H_LETTER;
        }

        for (int j = 0; j < columWidth; ++j)
        {
            cout << HORIZONTAL_LINE;
        }
    }

    cout << SYMBOL_SECOND_HALF_H_LETTER;
}

void printLowerTableFrame(int numberOfColumn, int columWidth)
{
    cout << LOWER_LEFT_CORNER;

    for (int j = 0; j < numberOfColumn; ++j)
    {
        for (int i = 0; i < columWidth; ++i)
        {
            cout << HORIZONTAL_LINE;
        }

        if ((numberOfColumn - 1) != j)
        {
            cout << SYMBOL_TURNED_T_WORD;
        }
        else
        {
            cout << LOWER_RIGHT_CORNER;
        }
    }

    cout << turnOffDECMode();
}

//void printTopTableFrame(int numberOfColumn, vector<int> columnWidth)
//{
//}

void printInnerTableFrame(/*int numberOfColumn, */vector<int> columnWidth)
{
    int numberOfColumn = columnWidth.size();

    //int numberBeforeLast = numberOfColumn

    cout << turnOnDECMode();

    for (int k = 0; k < numberOfColumn; ++k)
    {
        // если это не первый индекс
        if (FIRST_INDEX != k)
        {
            cout << SYMBOL_CROSS;
        }
        else
        {
            cout << SYMBOL_FIRST_HALF_H_LETTER;
        }

        for (int j = 0; j < columnWidth[k]; ++j)
        {
            cout << HORIZONTAL_LINE;
        }
    }

    cout << SYMBOL_SECOND_HALF_H_LETTER;
}

void printLowerTableFrame(vector<int> columnWidthValues)
{
    int numberOfColumns = columnWidthValues.size();

    cout << turnOnDECMode();

    cout << LOWER_LEFT_CORNER;

    for (int j = 0; j < numberOfColumns; ++j)
    {
        for (int i = 0; i < columnWidthValues[j]; ++i)
        {
            cout << HORIZONTAL_LINE;
        }

        if ((numberOfColumns - 1) != j)
        {
            cout << SYMBOL_TURNED_T_WORD;
        }
        else
        {
            cout << LOWER_RIGHT_CORNER;
        }
    }

    cout << turnOffDECMode();
}

//void printInnerTableFrame(int columnWidth)
//{
//    cout << turnOnDECMode();
//
//
//    // если это не первый и не последний индекс
//    if (FIRST_INDEX != i)
//    {
//        cout << SYMBOL_CROSS;
//    }
//    else
//    {
//        cout << SYMBOL_FIRST_HALF_H_LETTER;
//    }
//
//    for (int i = 0; i < columWidth; ++i)
//    {
//        cout << HORIZONTAL_LINE;
//    }
//
//    cout << SYMBOL_SECOND_HALF_H_LETTER;
//}