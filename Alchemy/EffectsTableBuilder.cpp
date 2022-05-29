#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder() : AlchemyTableBuilder()
{
	/*reset();*/
	//effectBuilder = new EffectBuilder();
	effectBuilder = nullptr;
}

EffectsTableBuilder::~EffectsTableBuilder()
{
	clear();
}

void EffectsTableBuilder::buildTable(AlchemyProgramParser* alchemyProgramParser)
{
	// ПАРСИМ

	// ЕСЛИ док был пустой и не спарсилось

	// Создаем эффекты сами

	// Создаем нового строителя ингредиентов
	effectBuilder = new EffectBuilder();

	// Добавить эффекты
	addEffects(NUMBER_OF_POSITIVE_EFFECTS, POSITIVE);
	addEffects(NUMBER_OF_NEGATIVE_EFFECTS, NEGATIVE);
}

void EffectsTableBuilder::addEffects(int numberOfEffects, bool isPositive)
{
	// Последний индекс в списке эффектов
	int lastIndex = numberOfEffects - 1;

	// В цикле добавляем эффекты в таблицу
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildEffect(lastIndex, isPositive);

		this->element->add(this->effectBuilder->getResult());

		// Уменьшаем последний индекс
		--lastIndex;
	}
}
//
//EffectsTable* EffectsTableBuilder::getResult()
//{
//	EffectsTable* res = this->effectsTable;
//
//	reset();
//
//	return res;
//}
//
//void EffectsTableBuilder::reset()
//{
//	effectsTable = new EffectsTable();
//}

void EffectsTableBuilder::clear()
{
	//if (nullptr != this->effectsTable)
	//{
	//	delete this->effectsTable;
	//	this->effectsTable = nullptr;
	//}

	AlchemyTableBuilder::clear();

	if (nullptr != this->effectBuilder)
	{
		delete this->effectBuilder;
		this->effectBuilder = nullptr;
	}
}
