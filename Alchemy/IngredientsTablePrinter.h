#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// Множитель для расчета длины таблицы

#define NUMBER_OF_COLUMNS		6		// Кол-во колонок
#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)
#define GAPS					2		// Кол-во пробелов в столбце (1 слева и 1 справа)




// Очередность столбцов id name price effect1 effect2 number

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

	// Расчитывает ширину каждого столбца и возвращает вектор
	vector<int> calculateColumnWidth(IngredientsTable* table) override;


	// Печать шапки таблицы
	void printTableHeader(IngredientsTable* table) override;
};

