#pragma once
#include "AlchemyProgram.h"
#include "AlchemyProgramParser.h"
#include "EffectsTableBuilder.h"


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

	// Задает таблицу эффектов
	void setEffectsTable(AlchemyProgramParser* alchemyProgramParse);

private:

	// Экземпляр программы алхимии
	AlchemyProgram* alchemyProgram;

	// Строитель таблицы эффектов
	EffectsTableBuilder* effectsTableBuilder;

	//IngredientsTableBuilder* 

	// Сбросить до начальных установок
	void reset();

	// Чистить память
	void clear();
};

