#pragma once
#include "TablePrinter.h"
#include "PotionTable.h"

#define PRICE_LENGTH				4		// Длина слова "Цена"
#define NUMBER_LENGTH				6		// Длина слова "Кол-во"
#define POWER_LENGTH				8		// Длина слова "Мощность"

#define NUMBER_OF_COLUMNS			5		// 4 колонки

class PotionTablePrinter : public TablePrinter<PotionTable>
{
public:

	PotionTablePrinter();

	~PotionTablePrinter() override;

	void print(int page) override;

	// заполнить вектор с содержимым таблицы
	void fillInTableContent() override;

	void printAvailableElements(int page) override;


private:

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

	// Печать содержимого таблицы
	void printContent(int page) override;

	// Печать доступного содержимого таблицы
	void printAvailableContent(int page) override;

#pragma endregion МЕТОДЫ ПЕЧАТИ



};

