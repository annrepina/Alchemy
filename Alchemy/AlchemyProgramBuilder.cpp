#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder() : Builder()
{
	/*reset();*/

	this->effectsTableBuilder = new EffectsTableBuilder();

	this->ingredientsTableBuilder = new IngredientsTableBuilder();

	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyProgramBuilder::~AlchemyProgramBuilder()
{
	clear();
}

//AlchemyProgram* AlchemyProgramBuilder::getResult()
//{
//	AlchemyProgram* res = this->alchemyProgram;
//
//	reset();
//
//	return res;
//}

void AlchemyProgramBuilder::buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse)
{
	/// Парсим

	// Если док пустой

	// Строим таблицу эффектов
	this->effectsTableBuilder->buildTable(alchemyProgramParse);

	// Присваиваем программе таблицу эффектов
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());

	// Присвоить строителю ингредиентов таблицу эффектов
	this->ingredientBuilder->setEffectsTable(this->element->getEffectsTable());

	// Заполняем список имен эффектов
	this->ingredientBuilder->fillEffectId();

	// Задаем строителя ингредиентов
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// Строим таблицу ингредиентов
	this->ingredientsTableBuilder->buildTable(alchemyProgramParse);

	// Присваиваем таблицу ингредиентов
	this->element->setIngredientsTable(ingredientsTableBuilder->getResult());

}

void AlchemyProgramBuilder::setEffectsTable(AlchemyProgramParser* alchemyProgramParse)
{
	// Строитель создает таблицу
	this->effectsTableBuilder->buildTable(alchemyProgramParse);

	// Добавляем таблицу в программу
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());
}

//void AlchemyProgramBuilder::reset()
//{
//	this->alchemyProgram = new AlchemyProgram();
//}

void AlchemyProgramBuilder::clear()
{
	// Вызываем ф-wb. у базового класса
	Builder::clear();

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}
