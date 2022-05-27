#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder()
{
	reset();

	this->effectsTableBuilder = new EffectsTableBuilder();

	this->ingredientsTableBuilder = new IngredientsTableBuilder();

	this->ingredientBuilder = new IngredientBuilder();
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

void AlchemyProgramBuilder::buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse)
{
	/// Парсим

	// Если док пустой

	// Строим таблицу эффектов
	this->effectsTableBuilder->buildEffectsTable(alchemyProgramParse);

	// Присваиваем программе таблицу эффектов
	this->alchemyProgram->setEffectsTable(this->effectsTableBuilder->getResult());

	// Присвоить строителю ингредиентов таблицу эффектов
	this->ingredientBuilder->setEffectsTable(this->alchemyProgram->getEffectsTable());

	// Заполняем список имен эффектов
	this->ingredientBuilder->fillEffectId();

	// Задаем строителя ингредиентов
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// Строим таблицу ингредиентов
	this->ingredientsTableBuilder->buildIngredientsTable(alchemyProgramParse);

	// Присваиваем таблицу ингредиентов
	this->alchemyProgram->setIngredientsTable(ingredientsTableBuilder->getResult());

}

void AlchemyProgramBuilder::setEffectsTable(AlchemyProgramParser* alchemyProgramParse)
{
	// Строитель создает таблицу
	this->effectsTableBuilder->buildEffectsTable(alchemyProgramParse);

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
