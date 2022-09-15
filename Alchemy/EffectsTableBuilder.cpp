#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder() : AlchemyTableBuilder()
{
	effectBuilder = nullptr;
}

EffectsTableBuilder::~EffectsTableBuilder()
{
	clear();
}

void EffectsTableBuilder::buildTable()
{
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

void EffectsTableBuilder::clear()
{
	AlchemyTableBuilder::clear();

	if (nullptr != this->effectBuilder)
	{
		delete this->effectBuilder;
		this->effectBuilder = nullptr;
	}
}