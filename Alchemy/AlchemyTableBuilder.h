#pragma once
#include "AlchemyLogicWriter.h"
#include "Builder.h"

// Строитель таблицы в программе зельеварение
template <typename Tab>
class AlchemyTableBuilder : public Builder<Tab>
{
public:

	// Конструктор по умолчанию
	AlchemyTableBuilder() : Builder<Tab>()
	{

	}

	// Построить таблицу
	virtual void buildTable() = 0;

};