#pragma once
#include "AlchemyProgram.h"


class AlchemyProgramBuilder
{
public:

	// Строитель по умолчанию
	AlchemyProgramBuilder();

	// Деструктор 
	~AlchemyProgramBuilder();

	// Получить результа
	AlchemyProgram* getResult();

	void buildAlchemyProgram();

private:

	// Экземпляр программы алхимии
	AlchemyProgram* alchemyProgram;

	// Сбросить до начальных установок
	void reset();

	// Чистить память
	void clear();
};

