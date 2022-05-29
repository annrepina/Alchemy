#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_PRINTING	10		// Координата Y для печати

// Класс- таблица
template<typename T>
class Table
{
public:

	// Конструктор по умолчанию
	Table()
	{
		title = "";
	}

	// Виртуальный деструктор
	virtual ~Table()
	{
	}

	//virtual void calculateXCoordForPrinting();

	virtual void add(T* element) = 0;

protected:

	// Название таблицы
	string title;

	//map<int, T*> elementWithId;


	//// Кол-во столбцов
	//int numberOfColumns;

	//// Кол-во строк
	//int numberOfLines;

	//// Длина
	//int length;

	//// Координат y для печати
	//int yCoordForPrinting;

	//// Координата х для печати
	//int xCoordForPrinting;

	//// Печать
	//virtual void print() = 0;




private:

};

