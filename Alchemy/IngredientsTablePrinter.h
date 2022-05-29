#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// Множитель для расчета длины таблицы

#define NUMBER_OF_COLUMNS		6		// Кол-во колонок
#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)

class IngredientsTablePrinter : public TablePrinter
{
public:

	IngredientsTablePrinter();


	

protected:

private:

	void calculateLength() override;

	// Вернуть наибольший id
	int calculateMaxIdStrSize();

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize();

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize();

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize();


};

