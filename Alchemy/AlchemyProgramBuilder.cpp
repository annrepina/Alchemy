#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder()
{
	reset();

	this->effectsTableBuilder = new EffectsTableBuilder();
}

AlchemyProgramBuilder::~AlchemyProgramBuilder()
{
	clear();
}

AlchemyProgram* AlchemyProgramBuilder::getResult()
{
	AlchemyProgram* res = this->alchemyProgram;

	reset();

	return res;
}

void AlchemyProgramBuilder::setEffectsTable(AlchemyProgramParser* alchemyProgramParse)
{
	// Строитель создает таблицу
	this->effectsTableBuilder->buildEffectstable(alchemyProgramParse);

	// Добавляем таблицу в программу
	this->alchemyProgram->setEffectsTable(this->effectsTableBuilder->getResult());
}

void AlchemyProgramBuilder::reset()
{
	this->alchemyProgram = new AlchemyProgram();
}

void AlchemyProgramBuilder::clear()
{
	if (nullptr != this->alchemyProgram)
	{
		delete this->alchemyProgram;
		this->alchemyProgram = nullptr;
	}

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}
