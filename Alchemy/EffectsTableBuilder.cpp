#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder()
{
	reset();
	//effectBuilder = new EffectBuilder();
	effectBuilder = nullptr;
}

EffectsTableBuilder::~EffectsTableBuilder()
{
	clear();
}

void EffectsTableBuilder::buildEffectstable(AlchemyProgramParser* alchemyProgramParser)
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
	// Последний индекс в списке позитивных эффектов
	int lastIndex = numberOfEffects - 1;

	// В цикле добавляем эффекты в таблицу
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildEffect(lastIndex, isPositive);

		this->effectsTable->addEffect(this->effectBuilder->getResult());

		// Уменьшаем последний индекс
		--lastIndex;
	}
}

EffectsTable* EffectsTableBuilder::getResult()
{
	EffectsTable* res = this->effectsTable;

	reset();

	return res;
}

void EffectsTableBuilder::reset()
{
	effectsTable = new EffectsTable();
}

void EffectsTableBuilder::clear()
{
	if (nullptr != this->effectsTable)
	{
		delete this->effectsTable;
		this->effectsTable = nullptr;
	}

	if (nullptr != this->effectBuilder)
	{
		delete this->effectBuilder;
		this->effectBuilder = nullptr;
	}
}

//void EffectsTableBuilder::addPositiveEffects(int numberOfEffects)
//{
//	// Последний индекс в списке позитивных эффектов
//	int lastIndex = NUMBER_OF_POSITIVE_EFFECTS - 1;
//
//	// В цикле добавляем эффекты в таблицу
//	for (int i = 0; i < numberOfEffects; ++i)
//	{
//		this->effectBuilder->buildPositiveEffect(lastIndex);
//
//		this->effectstable->addEffect(this->effectBuilder->getResult());
//
//		// Уменьшаем последний индекс
//		--lastIndex;
//	}
//}
//
//void EffectsTableBuilder::addNegativeEffects(int numberOfEffects)
//{
//	// Последний индекс в списке негативных эффектов
//	int lastIndex = NUMBER_OF_NEGATIVE_EFFECTS - 1;
//
//	// В цикле добавляем эффекты в таблицу
//	for (int i = 0; i < numberOfEffects; ++i)
//	{
//		this->effectBuilder->buildNegativeEffect(lastIndex);
//
//		this->effectstable->addEffect(this->effectBuilder->getResult());
//
//		// Уменьшаем последний индекс
//		--lastIndex;
//	}
//}
