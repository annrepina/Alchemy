#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

// Класс- таблица
class Table
{
public:

	// Конструктор по умолчанию
	Table();

protected:

	// Название таблицы
	string title;

	// Кол-во колонок
	int numberOfColumns;

	// Кол-во линий
	int numberOfLines;

	int length;

	virtual void print() const;

	virtual void calculateLength() = 0;

private:

	


};

