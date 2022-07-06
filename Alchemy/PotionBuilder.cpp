#include "PotionBuilder.h"

PotionBuilder::PotionBuilder() : Builder()
{
}

void PotionBuilder::buildPotion(Ingredient* ingredient1, Ingredient* ingredient2)
{
	// результат смешения ингредиентов
	bool res = false;

	// id эффекта, который совпал
	int effectId;

	// Итератор на начало map с id эффектов первого ингредиента
	auto firstBeginIter = ingredient1->getBeginIteratorOfEffectsId();
	// Итератор на конец map с id эффектов первого ингредиента
	auto firstEndIter = ingredient1->getEndIteratorOfEffectsId();

	// Итератор на начало map с id эффектов второго ингредиента
	auto secondBeginIter = ingredient2->getBeginIteratorOfEffectsId();
	// Итератор на конец map с id эффектов второго ингредиента
	auto secondEndIter = ingredient2->getEndIteratorOfEffectsId();

	// в цикле проверяем эффекты на совпадение
	for (auto i = firstBeginIter; i != firstEndIter; ++i)
	{
		for (auto j = secondBeginIter; j != secondEndIter; ++j)
		{
			// если id равны
			if (i->first == j->first)
			{
				res = true;

				// задаем параметры для зелья
				this->element->setEffectId(i->first);
				this->element->setNumber(1);
				this->element->setPrice(ingredient1->getPrice() + ingredient2->getPrice());

				// делаем узнаваемым эффект у обоих ингредиентов
				ingredient1->openEffect(i->first);
				ingredient2->openEffect(i->first);

				break;
			}
		}

		if (res)
			break;
	}
}
