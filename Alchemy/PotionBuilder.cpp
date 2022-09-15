#include "PotionBuilder.h"

int PotionBuilder::coefficientOfPower = COEFFICIENT_OF_POWER;

int PotionBuilder::coefficientOfPrice = COEFFICIENT_OF_PRICE;

PotionBuilder::PotionBuilder() : Builder()
{
}

void PotionBuilder::buildPotion(Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist)
{
	// ������ id ��������, ������� �������
	vector<int> equalEffectsId = findEqualEffects(ingredient1, ingredient2);

	// id �������, ������� ������
	int effectId = -1;

	// ���� ������ �� ������
	if (equalEffectsId.size() > 0)
	{
		// �������� �� ������� ����������� ������ id ������� 
		effectId = randInRange(0, equalEffectsId.size() - 1);

		effectId = equalEffectsId[effectId];

		setPotion(effectId, ingredient1, ingredient2, alchemist);
	}
}

vector<int> PotionBuilder::findEqualEffects(Ingredient* ingredient1, Ingredient* ingredient2)
{
	// ������ id ��������, ������� �������
	vector<int> equalEffectsId;

	// �������� �� ������ map � id �������� ������� �����������
	auto firstBeginIter = ingredient1->getBeginIteratorOfEffectsId();
	// �������� �� ����� map � id �������� ������� �����������
	auto firstEndIter = ingredient1->getEndIteratorOfEffectsId();

	// �������� �� ������ map � id �������� ������� �����������
	auto secondBeginIter = ingredient2->getBeginIteratorOfEffectsId();
	// �������� �� ����� map � id �������� ������� �����������
	auto secondEndIter = ingredient2->getEndIteratorOfEffectsId();

	// � ����� ��������� ������� �� ����������
	for (auto i = firstBeginIter; i != firstEndIter; ++i)
	{
		for (auto j = secondBeginIter; j != secondEndIter; ++j)
		{
			// ���� id �����
			if (i->first == j->first)
			{
				// ��������� � ������ ��������
				equalEffectsId.push_back(i->first);

				break;
			}
		}
	}

	return equalEffectsId;
}

void PotionBuilder::setPotion(int effectId, Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist)
{
	// ������ ��������� ��� �����
	this->element->setEffectId(effectId);
	this->element->setNumber(1);

	// ������� ��������
	int alchemistLevel = alchemist->getAlchemistLevel() / LEVEL_DIVISOR;
	int salesmanLevel = alchemist->getSalesmanLevel() / LEVEL_DIVISOR;

	// ���� ������ ����� ���������, �� ����������� �� 1, ����� �� �������� �� 0
	if (alchemistLevel == 0)
		alchemistLevel = 1;

	if (salesmanLevel == 0)
		salesmanLevel = 1;

	// ����������� ���� �����
	this->element->setPrice((ingredient1->getPrice() + ingredient2->getPrice()) + (coefficientOfPrice * alchemistLevel * salesmanLevel));

	this->element->setPower(coefficientOfPower * alchemistLevel);

	// ������ ���������� ������ � ����� ������������
	ingredient1->openEffect(effectId);
	ingredient2->openEffect(effectId);

	// ����������� ������� ��������
	alchemist->increaseAlchemistLevel();
}