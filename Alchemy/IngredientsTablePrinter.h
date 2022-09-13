#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"
#include "IObserver.h"
#include "ServiceFunctions.h"

#define MULTIPLIER									3		// Множитель для расчета длины таблицы

#define OUTER_BORDERS								2		// Внешние границы таблицы (левая и правая)
#define GAPS										2		// Кол-во пробелов в столбце (1 слева и 1 справа)
#define NUMBER_OF_COLUMNS							6		// Кол-во колонок
#define NUMBER_OF_COLUMN_WITH_NUMBER_OF_INGREDIENTS	6		// Номер колонки, в которой находится кол-во ингредиентов

#define PRICE_LENGTH								4		// Длина слова "Цена"
#define NUMBER_LENGTH								6		// Длина слова "Кол-во"

#define UNKNOWN_EFFECT								"НЕИЗВЕСТНО"	// если эффект у данного ингредиента неизветстен

// Цифровые столбцы в таблице
#define INGREDIENT_TABLE_DIGIT_COLUMN_1			1	// Столбец 1
#define INGREDIENT_TABLE_DIGIT_COLUMN_3			3	// Столбец 3
#define INGREDIENT_TABLE_DIGIT_COLUMN_6			6	// Столбец 6

#define INDEX_IF_CONTENT_OF_NUMBER_COLUMN		5	// Индекс контента колонки с кол-вом

// Класс, печатающий таблицу ингредиентов - принтер таблицы ингредиентов
class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	// Конструктор по умолчанию
	IngredientsTablePrinter();

	// Деструктор
	~IngredientsTablePrinter() override;

	// Печать таблицы
	void print(int page) override;

	// Печать передаваемого напрямую принтеру контента таблицы
	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	// Печать с маркерами сортировкти
	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	// Печать доступных элементов, кол-во у которых больше нуля
	void printAvailableElements(int page) override;

	// заполнить вектор с содержимым таблицы
	void fillInTableContent() override;

	// Расчитать данные для печати
	void calculateData() override;

	// Геттер кол-ва доступных элементов
	int getNumberOfAvailableContent();

private:

	// Кол-во доступных пользователю элементов
	int numberOfAvailableContent;

#pragma region МЕТОДЫ РАСЧЕТА
	
	// Рассчитать кол-во строк в таблице
	int calculateNumberOfLines() override;

	// Рассчитать ширину таблицы
	int calculateWidth() override;

	// посчитать размер числа - максимального id
	int calculateMaxId() override;

	// Посчитать размер самого длинного название ингредиента
	int calculateMaxNameSize() override;

	// Посчитать размер числа - наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize() override;

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize();

	// Расчитывает ширину каждого столбца и возвращает вектор
	vector<int> calculateColumnWidth() override;

	// Посчитать кол-во доступных пользователю ингредиентов
	int calculateNumberOfAvailableElements();

#pragma endregion МЕТОДЫ РАСЧЕТА

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать шапки таблицы
	void printHeader() override;

	// Печать шапки таблицы с маркерами сортировки
	void printHeader(int numberOfColumn, bool ordreOfSorting) override;

	// Печать содержимого таблицы
	void printContent(int page) override;

	// Печать контента передаваемого принтеру
	void printContent(vector<vector<string>> content, int page) override;

	// Печать доступного содержимого таблицы
	void printAvailableContent(int page) override;

#pragma endregion МЕТОДЫ ПЕЧАТИ

	// Изменитm контент для печати определенного ингредиента по id 
	void changeTableContentForOneElement(int id) override;

	// Изменитm контент для печати определенного ингредиента по id с учетом кол-ва
	void changeTableContentForOneElement(int id, int previousNumber) override;

	// Обновить содержимое таблицы - добавить новый ингредиент
	void addElementToTableContent(int id) override;
};