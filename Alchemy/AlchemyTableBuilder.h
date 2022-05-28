#pragma once
#include "AlchemyProgramParser.h"

// Строитель таблицы
class AlchemyTableBuilder
{
public:

	// Конструктор по умолчанию
	AlchemyTableBuilder();

	// Деструктор
	virtual ~AlchemyTableBuilder() = 0;

	// Построить таблицу
	virtual void buildTable(AlchemyProgramParser* alchemyProgramParser) = 0;

protected:

	// Сборосить до начальных установок
	virtual void reset() = 0;

	// Чистит память
	virtual void clear() = 0;

	//// Расчитать длину таблицы
	//virtual void calculateLength() = 0;

private:



};

