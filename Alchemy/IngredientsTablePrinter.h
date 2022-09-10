#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"
#include "IObserver.h"
#include "ServiceFunctions.h"

#define MULTIPLIER									3		// Множитель для расчета длины таблицы

//#define NUMBER_OF_COLUMNS							6		// Кол-во колонок
#define OUTER_BORDERS								2		// Внешние границы таблицы (левая и правая)
#define GAPS										2		// Кол-во пробелов в столбце (1 слева и 1 справа)
#define NUMBER_OF_COLUMNS							6		// Кол-во колонок
#define NUMBER_OF_COLUMN_WITH_NUMBER_OF_INGREDIENTS	6		// Номер колонки, в которой находится кол-во ингредиентов

#define PRICE_LENGTH								4		// Длина слова "Цена"
#define NUMBER_LENGTH								6		// Длина слова "Кол-во"

#define UNKNOWN_EFFECT				"НЕИЗВЕСТНО"	// если эффект у данного ингредиента неизветстен


// Цифровые столбцы в таблице
//#define COLUMN_1			1	// Столбец 1
//#define COLUMN_3			3	// Столбец 3
//#define COLUMN_6			6	// Столбец 6

// Цифровые столбцы в таблице
#define INGREDIENT_TABLE_DIGIT_COLUMN_1			1	// Столбец 1
#define INGREDIENT_TABLE_DIGIT_COLUMN_3			3	// Столбец 3
#define INGREDIENT_TABLE_DIGIT_COLUMN_6			6	// Столбец 6

#define INDEX_IF_CONTENT_OF_NUMBER_COLUMN		5	// Индекс контента колонки с кол-вом

// Очередность столбцов id name price effect1 effect2 number

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	IngredientsTablePrinter();

	~IngredientsTablePrinter() override;

	void print(int page) override;

	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	void printAvailableElements(int page) override;

	// заполнить вектор с содержимым таблицы
	void fillInTableContent() override;

	void calculateData() override;

	int getNumberOfAvailableContent();

private:

	// Кол-во доступных пользователю элементов
	int numberOfAvailableContent;

	//int numberOfelement

#pragma region МЕТОДЫ РАСЧЕТА
	
	// Рассчитать кол-во строк в таблице
	int calculateNumberOfLines() override;

	// Рассчитать ширину таблицы
	int calculateWidth() override;

	// посчитать максимальное id
	int calculateMaxId() override;

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize() override;

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize() override;

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize();

	// Расчитывает ширину каждого столбца и возвращает вектор
	vector<int> calculateColumnWidth() override;

	// Посчитать кол-во доступных пользователю ингредиентов
	int calculateNumberOfAvailableElements();

	// Добавить id доступных элементов если вектор пустой
	void calculateAvailableElementsId();

#pragma endregion МЕТОДЫ РАСЧЕТА

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать шапки таблицы
	void printHeader() override;

	void printHeader(int numberOfColumn, bool ordreOfSorting) override;

	// Печать содержимого таблицы
	void printContent(int page) override;

	void printContent(vector<vector<string>> content, int page) override;

	// Печать доступного содержимого таблицы
	void printAvailableContent(int page) override;

#pragma endregion МЕТОДЫ ПЕЧАТИ

	// заполнить один элемент вектора содержимым таблицы
	void changeTableContentForOneElement(int id) override;

	void changeTableContentForOneElement(int id, int previousNumber) override;

	// Обновить содержимое таблицы - добавить новый ингредиент
	void addElementToTableContent(int id) override;
};

