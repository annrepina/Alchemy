#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder()
{
	effectstable = new EffectsTable();
	effectBuilder = nullptr;
}

void EffectsTableBuilder::setEffectstable(AlchemyProgramParser* alchemyProgramParser)
{
	// ПАРСИМ

	// ЕСЛИ док был пустой и не спарсилось

	// Создаем эффекты сами

	// Создаем нового строителя ингредиентов
	effectBuilder = new EffectBuilder();
}

void EffectsTableBuilder::addPositiveEffects(int numberOfEffects)
{
	// Последний индекс в списке блюд и напитков
	int lastIndex = NUMBER_OF_POSITIVE_EFFECTS - 1;

	// В цикле добавляем приемы пищи в меню
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildPositiveEffect(lastIndex);

		this->effectstable->addEffect(this->effectBuilder->getResult());

		// Уменьшаем последний индекс
		--lastIndex;
	}
}
