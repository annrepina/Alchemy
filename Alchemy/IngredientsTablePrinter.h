#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// Множитель для расчета длины таблицы

//#define NUMBER_OF_COLUMNS		6		// Кол-во колонок
#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)
#define GAPS					2		// Кол-во пробелов в столбце (1 слева и 1 справа)


#define PRICE_LENGTH				4		// Длина слова "Цена"
#define NUMBER_LENGTH				6		// Длина слова "Кол-во"

#define UNKNOWN_EFFECT				"НЕИЗВЕСТНО"	// если эффект у данного ингредиента неизветстен

// Очередность столбцов id name price effect1 effect2 number

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	IngredientsTablePrinter();

	//void print(IngredientsTable* ingredientsTable) override;

	void print(IngredientsTable* table, int page) override;

protected:

private:

#pragma region МЕТОДЫ РАСЧЕТА
	
	// Рассчитать кол-во строк в таблице
	int calculateNumberOfLines(IngredientsTable* table) override;

	// Рассчитать ширину таблицы
	int calculateWidth(IngredientsTable* table) override;

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

#pragma endregion МЕТОДЫ РАСЧЕТА

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать шапки таблицы
	void printHeader() override;

	// Печать содержимого таблицы
	void printContent(IngredientsTable* table, int page) override;

#pragma endregion МЕТОДЫ ПЕЧАТИ

	// заполнить вектор с содержимым таблицы
	void fillInTableContent(IngredientsTable* table) override;

	//// Печать шапки таблицы
	//void printHeader(IngredientsTable* table) override;

	// Печать внутренней рамки таблицы
	//void printInnerFrame(IngredientsTable* table) override;
};

