#include "PotionBuilder.h"

int PotionBuilder::coefficientOfPower = COEFFICIENT_OF_POWER;

int PotionBuilder::coefficientOfPrice = COEFFICIENT_OF_PRICE;

PotionBuilder::PotionBuilder() : Builder()
{
}

void PotionBuilder::buildPotion(Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist)
{
	// Вектор id эффектов, которые совпали
	vector<int> equalEffectsId = findEqualEffects(ingredient1, ingredient2);

	// id эффекта, который совпал
	int effectId = -1;

	// если вектор не пустой
	if (equalEffectsId.size() > 0)
	{
		// рандомно из вектора вытаскиваем индекс id эффекта 
		effectId = randInRange(0, equalEffectsId.size() - 1);

		effectId = equalEffectsId[effectId];

		setPotion(effectId, ingredient1, ingredient2, alchemist);
	}
}

vector<int> PotionBuilder::findEqualEffects(Ingredient* ingredient1, Ingredient* ingredient2)
{
	// Вектор id эффектов, которые совпали
	vector<int> equalEffectsId;

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
				// Добавляем в вектор эффектов
				equalEffectsId.push_back(i->first);

				break;
			}
		}
	}

	return equalEffectsId;
}

void PotionBuilder::setPotion(int effectId, Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist)
{
	// задаем параметры для зелья
	this->element->setEffectId(effectId);
	this->element->setNumber(1);

	// уровень алхимика
	int alchemistLevel = alchemist->getAlchemistLevel() / LEVEL_DIVISOR;
	int salesmanLevel = alchemist->getSalesmanLevel() / LEVEL_DIVISOR;

	// если уровни самые маленькие, то увеличиваем до 1, чтобы не умножать на 0
	if (alchemistLevel == 0)
		alchemistLevel = 1;

	if (salesmanLevel == 0)
		salesmanLevel = 1;

	// расчитываем цену зелья
	this->element->setPrice((ingredient1->getPrice() + ingredient2->getPrice()) + (coefficientOfPrice * alchemistLevel * salesmanLevel));

	this->element->setPower(coefficientOfPower * alchemistLevel);

	// делаем узнаваемым эффект у обоих ингредиентов
	ingredient1->openEffect(effectId);
	ingredient2->openEffect(effectId);

	// увеличиваем уровень алхимика
	alchemist->increaseAlchemistLevel();
}