#pragma once
#include "TablePrinter.h"
#include "PotionTable.h"

// Длины слов - названий шапок
#define PRICE_LENGTH				4		// Длина слова "Цена"
#define NUMBER_LENGTH				6		// Длина слова "Кол-во"
#define POWER_LENGTH				8		// Длина слова "Мощность"

#define NUMBER_OF_COLUMNS			5		// 5 колонок

// Цифровые столбцы в таблице
#define NON_DIGIT_COLUMN			2	// Столбец 2
#define COLUMN_1					1	// Столбец 1
#define COLUMN_3					3	// Столбец 3
#define COLUMN_4					4	// Столбец 4
#define COLUMN_5					5	// Столбец 5

// Класс, печатающий таблицу зелий - принтер таблицы зелий
class PotionTablePrinter : public TablePrinter<PotionTable>
{
public:

	// Конструктор по умолчанию
	PotionTablePrinter();

	// Деструктор
	~PotionTablePrinter() override;

	// Печать таблицы
	void print(int page) override;

	// Печать передаваемого контента таблицы
	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	// Печать с маркерами сортировки
	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	// Печать доступных элементов, кол-во которых больше нуля
	void printAvailableElements(int page) override;

	// заполнить вектор с содержимым таблицы
	void fillInTableContent() override;

	// Расчитать данные для печати
	void calculateData() override;

	// Обновление контента для печати после измения таблицы зелий
	void update() override;

private:

#pragma region МЕТОДЫ РАСЧЕТА

	// Рассчитать кол-во строк в таблице
	int calculateNumberOfLines() override;

	// Расчитывает ширину каждого столбца и возвращает вектор
	vector<int> calculateColumnWidth() override;

	// Рассчитать ширину таблицы
	int calculateWidth() override;

	// посчитать размер числа - максимального id зелья
	int calculateMaxId() override;

	// Рассчитать размер самого длинного названия зелий
	int calculateMaxNameSize() override;

	// Рассчитать размер числа - наибольшего кол-ва зелий
	int calculateMaxNumberStrSize() override;

	// Рассчитать макс размер стрингового отображения максимальной мощности зелий
	int calculateMaxPowerStrSize();

	// Расчитать макс размер - стрингового отображения цены
	int calculateMaxPriceStrSize();

#pragma endregion МЕТОДЫ РАСЧЕТА

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать шапки таблицы
	void printHeader() override;

	// Печать шапки таблицы с маркерами сортировки
	void printHeader(int numberOfColumn, bool ordreOfSorting) override;

	// Печать содержимого таблицы
	void printContent(int page) override;

	// Печать контента таблицы, передаваемого в ф-цию
	void printContent(vector<vector<string>> content, int page) override;

	// Печать доступного содержимого таблицы
	void printAvailableContent(int page) override;

#pragma endregion МЕТОДЫ ПЕЧАТИ

	// Изменить контент определенного зелья
	void changeTableContentForOneElement(int id) override;

	// зИзменить контент определенного зелья с учетом кол-ва
	void changeTableContentForOneElement(int id, int previousNumber) override;

	// Обновить содержимое таблицы - добавить новое зелье
	void addElementToTableContent(int id) override;

	// Найти индекс искомого элемента в таблице контента по id
	int findIndexInTableContentByKey(int id);
};