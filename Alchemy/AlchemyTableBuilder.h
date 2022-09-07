#pragma once
#include "AlchemyLogicWriter.h"
#include "Builder.h"

// Строитель таблицы
template <typename Tab>
class AlchemyTableBuilder : public Builder<Tab>
{
public:

	// Конструктор по умолчанию
	AlchemyTableBuilder() : Builder<Tab>()
	{

	}

	//// Деструктор
	//virtual ~AlchemyTableBuilder() = 0;

	// Построить таблицу
	virtual void buildTable(AlchemyLogicWriter* alchemyLogicWriter) = 0;

protected:

	//// Сборосить до начальных установок
	//virtual void reset() = 0;

	//// Чистит память
	//virtual void clear() = 0;

private:



};

