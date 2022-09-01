#pragma once
#include "TablePrinter.h"
#include "PotionTable.h"

#define PRICE_LENGTH				4		// Длина слова "Цена"
#define NUMBER_LENGTH				6		// Длина слова "Кол-во"
#define POWER_LENGTH				8		// Длина слова "Мощность"

#define NUMBER_OF_COLUMNS			5		// 5 колонок

class PotionTablePrinter : public TablePrinter<PotionTable>/*, public IObserver*/
{
public:

	PotionTablePrinter();

	~PotionTablePrinter() override;

	void print(int page) override;

	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	// заполнить вектор с содержимым таблицы
	void fillInTableContent() override;

	void printAvailableElements(int page) override;

	void update() override;

private:

	//void update(int id) override;

#pragma region МЕТОДЫ РАСЧЕТА

	// Рассчитать кол-во строк в таблице
	int calculateNumberOfLines() override;

	// Расчитывает ширину каждого столбца и возвращает вектор
	vector<int> calculateColumnWidth() override;

	// Рассчитать ширину таблицы
	int calculateWidth() override;

	// посчитать максимальное id
	int calculateMaxId() override;

	//// Вернуть наибольший id
	//int calculateMaxIdStrSize() override;

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize() override;

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize() override;

	// Рассчитать макс длину стрингового отображения мощности зелья
	int calculateMaxPowerStrSize();

	// Расчитать макс длину стрингового отображения цены
	int calculateMaxPriceStrSize();

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

	// заполнить один элемент вектора содержимым таблицы
	void changeTableContentForOneElement(int id, int previousNumber) override;

	// Обновить содержимое таблицы - добавить новый ингредиент
	void addElementToTableContent(int id) override;

	// Найти индекс искомого элемента в таблице контента по ключу
	int findIndexInTableContentByKey(int key);
};

