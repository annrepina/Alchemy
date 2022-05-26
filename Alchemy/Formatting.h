#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

/* Коды RGB */

/* Для экрана - 16-чные значения */
// Светло-желтый цвет экрана
#define R_YELLOW			"e5"      
#define G_YELLOW			"dc"         
#define B_YELLOW			"8b"

// Светло-голубой цвет экрана
#define R_BLUE				"99"      
#define G_BLUE				"ff"         
#define B_BLUE				"ff"

// Светло-зеленый цвет экрана
#define R_LIGHT_GREEN		"e5"
#define G_LIGHT_GREEN		"e1"
#define B_LIGHT_GREEN		"cc"


// Белый цвет экрана
#define WHITE_DEFAULT_16	"FF"      // Белый цвет фона


/* Коды атрибутов переднего и заднего планов - 10-чные значения */
#define DEFAULT				"0"      // код возвращения всех атрибутов текста в состояние по умолчанию до изменения
#define WHITE_DEFAULT_10	"255"    // код цвета заднего плана - белый

// Светло-бирюзовый цвет
#define R_AQUAMARINE        "35"
#define G_AQUAMARINE        "222"
#define B_AQUAMARINE        "203"

// Серый цвет
#define R_DECIMAL_GREY		"96"
#define G_DECIMAL_GREY		"96"
#define B_DECIMAL_GREY		"96"



/* Коды для стирания вывода с экрана консоли */
#define FROM_CURSOR_TO_SCREEN_END	"0"	// Очищает все данные с текущей позиции курсора(включительно) до конца строки или экрана									
#define FROM_SCREEN_START_TO_CURSOR "1"	// Очищает все данные с начала строки или экрана до текущей позиции курсора(включительно)
#define WHOLE_SCREEN				"2" // Очищает всю строку или экран.

/* Виртуальные коды клавиш клавиатуры */
#define VK_ESCAPE	0x1B	// ESC key
#define VK_RETURN	0x0D	// ENTER key

/* Графические символы в кодировке DEC */
#define TOP_LEFT_CORNER				"l"      // верхний левый угол
#define HORIZONTAL_LINE				"q"      // горизонтальная линия
#define TOP_RIGHT_CORNER			"k"      // верхний правый угол
#define VERTICAL_LINE				"x"      // вертикальная линия
#define LOWER_LEFT_CORNER			"m"      // нижний левый угол
#define LOWER_RIGHT_CORNER			"j"      // верхний правый угол
#define SYMBOL_T_WORD				"w"		 // сивол '┬'
#define SYMBOL_TURNED_T_WORD		"v"		 // сивол '┴'
#define SYMBOL_FIRST_HALF_H_WORD	"t"		 // сивол '├'
#define SYMBOL_SECOND_HALF_H_WORD	"u"		 // сивол '┤'
#define SYMBOL_CROSS				"n"		 // сивол '┼'
#define CELL						"a"      // клетка

/* Индексы */
#define FIRST_INDEX					 0		 // Первый индекс

// Устанавливает курсор в определенные координаты
string goToXY(int yCoord, int xCoord);

// возвращает координаты курсора в начало
void goToStart();

// Форматирование текста
string changeTextFormat(string param);

// Печатает ноль
void printNull(int parametr);

// Стирает вывод на экране в зависимости от параметра
string eraseOnScreen(string param);

// Изменяет фон экрана (работает только с параметрами в 16-чной системе исчесления)
string changeScreenBackground(string r, string g, string b);

// Установка для цвета переднего плана значения RGB
// необходимо, потому что на фоне, заданном RGB, стандартные цвета консоли отображаются некорректно
// Работает только в 10-чной системе исчесления
string changeForegroundColorsExtra(string r, string g, string b);

// Установка дополнительных цветов для фона
// Работает только в 10-чной системе исчесления
string changeBackgroundColorsExtra(string r, string g, string b);

// Изменение названия окна консоли
string changeWindowTitle(string str);

#pragma region Функции сброса параметров

// Сбрасывает цвет фона до черного
string resetScreenColorToBlack();

// Сбрасывает цвет фона до белого
string resetScreenColorToWhite();

// Сбрасывает цвет переднего фона (текста) до черного
string resetForegroundColorToBlack();

// Сбрасывает цвет заднего фона до черного (при применении доп.цветов rgb до этого)
string resetExtraBackgroundColorToBlack();

// Сброс всех параметров цветов
string resetColorParams();

#pragma endregion 

#pragma region Функции печати текста в рамке

// Печатает заголовок в рамке с изменением цвета фона стандартными цветами
void printFramedText(string title, int yCoord, int xCoord, string param1, string param2);

// Печатает заголовок в рамке с изменением цвета фона цветами rgb, НО без изменения шрифта
void printFramedText(string text, int yCoord, int xCoord, string r, string g, string b);

// Печатает заголовок в рамке БЕЗ изменений фона
void printFramedText(string text, int yCoord, int xCoord);

#pragma endregion

// Печать текста с другим цветом фона
void printTextWithBackground(string text, string r, string g, string b);

// Печать цветного текста
void printColoredText(string text, string r, string g, string b);

// переходит по координатам, а после увеличивает Y координату
void goToCoordAndIncreaseY(int& yCoord, int xCoord);

// Включает режим рисования линии DEC
string turnOnDECMode();

// Выключает режим рисования линии DEC
string turnOffDECMode();

// Возвращает ширину консоли
int calculateConsoleWidth();

#pragma region Функции для печати таблицы с одинаковой шириной колонок и строчек с высотой 1

// Печатает верхнюю рамку таблицы
void printTopTableFrame(int numberOfColumn, int columWidth);

// Печатает внутреннюю границу твблицы
void printInnerTableFrame(int numberOfColumn, int columWidth);

// Печатает нижнюю рамку таблицы
void printLowerTableFrame(int numberOfColumn, int columWidth);

#pragma endregion








