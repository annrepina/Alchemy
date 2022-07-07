#include "PotionBuilder.h"

int PotionBuilder::coefficientOfPower = COEFFICIENT_OF_POWER;

int PotionBuilder::coefficientOfPrice = COEFFICIENT_OF_PRICE;

PotionBuilder::PotionBuilder() : Builder()
{
}

void PotionBuilder::buildPotion(Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist)
{
	// ��������� �������� ������������
	bool res = false;

	// id �������, ������� ������
	int effectId;

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
				res = true;

				// ������ ��������� ��� �����
				this->element->setEffectId(i->first);
				this->element->setNumber(1);

				// ������� ��������
				int alchemistLevel = alchemist->getAlchemistLevel();
				int salesmanLevel = alchemist->getSalesmanLevel();

				// ���� ������ ����� ���������, �� ����������� �� 1, ����� �� �������� �� 0
				if (alchemistLevel == 0)
					alchemistLevel = 1;

				if (salesmanLevel == 0)
					salesmanLevel = 1;

				// ����������� ���� �����
				this->element->setPrice((ingredient1->getPrice() + ingredient2->getPrice()) + (coefficientOfPrice * alchemistLevel * salesmanLevel));

				// ������ ���������� ������ � ����� ������������
				ingredient1->openEffect(i->first);
				ingredient2->openEffect(i->first);

				// ����������� ������� ��������
				alchemist->increaseAlchemistLevel();

				break;
			}
		}

		if (res)
			break;
	}
}
