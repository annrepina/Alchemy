#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_FRAME_PRINTING	10		// Координата Y для печати

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

	virtual void add(T* element) = 0;

	string getTitle() 
	{
		return this->title;
	}

protected:

	// Название таблицы
	string title;

private:

};

