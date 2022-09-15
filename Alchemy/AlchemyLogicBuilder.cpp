#include "AlchemyLogicBuilder.h"

AlchemyLogicBuilder::AlchemyLogicBuilder() : Builder()
{
	this->effectsTableBuilder = new EffectsTableBuilder();
	this->ingredientsTableBuilder = new IngredientsTableBuilder();
	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyLogicBuilder::~AlchemyLogicBuilder()
{
	clear();
}

void AlchemyLogicBuilder::buildAlchemyProgram()
{
	// Создаем пустого алхимика
	this->element->setAlchemist(new Alchemist);

	// Строим таблицу эффектов
	this->effectsTableBuilder->buildTable();

	// Присваиваем программе таблицу эффектов
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());

	// Присвоить строителю ингредиентов таблицу эффектов
	this->ingredientBuilder->setEffectsTable(this->element->getEffectsTable());

	// Заполняем список имен эффектов
	this->ingredientBuilder->fillEffectId();

	// Задаем строителя ингредиентов
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// Строим таблицу ингредиентов
	this->ingredientsTableBuilder->buildTable();

	// Присваиваем таблицу ингредиентов
	this->element->setIngredientsTable(ingredientsTableBuilder->getResult());

	// Добавляем новую пустую таблицу зелий
	this->element->setPotionTable(new PotionTable);

	// Задаем таблицу эффектов таблице зелий
	this->element->getPotionTable()->setEffectsTable(this->element->getEffectsTable());
}

void AlchemyLogicBuilder::setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter)
{
	// Строитель создает таблицу
	this->effectsTableBuilder->buildTable();

	// Добавляем таблицу в программу
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());
}

void AlchemyLogicBuilder::clear()
{
	// Вызываем ф-wb. у базового класса
	Builder::clear();

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}