#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// Множитель для расчета длины таблицы

#define NUMBER_OF_COLUMNS		6		// Кол-во колонок
#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	IngredientsTablePrinter();

	void print(IngredientsTable* ingredientsTable) override;

protected:

private:

	void calculateLength(IngredientsTable* ingredientsTable) override;

	// Вернуть наибольший id
	int calculateMaxIdStrSize(IngredientsTable* table) override;

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize(IngredientsTable* table) override;

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize(IngredientsTable* table);

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize(IngredientsTable* table);

	// Печать шапки таблицы
	void printTableHeader(IngredientsTable* table) override;
};

