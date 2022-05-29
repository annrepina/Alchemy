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
	int calculateMaxIdStrSize(Table* table);

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize();

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize();

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize();


};

