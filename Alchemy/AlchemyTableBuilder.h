#pragma once
#include "AlchemyProgramParser.h"
#include "Builder.h"

// Строитель таблицы
class AlchemyTableBuilder : public Builder
{
public:

	// Конструктор по умолчанию
	AlchemyTableBuilder();

	//// Деструктор
	//virtual ~AlchemyTableBuilder() = 0;

	// Построить таблицу
	virtual void buildTable(AlchemyProgramParser* alchemyProgramParser) = 0;

protected:

	//// Сборосить до начальных установок
	//virtual void reset() = 0;

	//// Чистит память
	//virtual void clear() = 0;

private:



};

