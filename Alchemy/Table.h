#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_PRINTING	10		// Координата Y для печати

// Класс- таблица
class Table
{
public:

	// Конструктор по умолчанию
	Table();

	// Виртуальный деструктор
	virtual ~Table();

	virtual void calculateXCoordForPrinting();

protected:

	// Название таблицы
	string title;

	// Кол-во столбцов
	int numberOfColumns;

	//// Кол-во строк
	//int numberOfLines;

	// Длина
	int length;

	// Координат y для печати
	int yCoordForPrinting;

	// Координата х для печати
	int xCoordForPrinting;

	// Печать
	virtual void print() = 0;




private:

};

