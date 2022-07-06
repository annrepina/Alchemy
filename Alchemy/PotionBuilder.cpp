#include "PotionBuilder.h"

PotionBuilder::PotionBuilder() : Builder()
{
}

void PotionBuilder::buildPotion(Ingredient* ingredient1, Ingredient* ingredient2)
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
				this->element->setPrice(ingredient1->getPrice() + ingredient2->getPrice());

				// ������ ���������� ������ � ����� ������������
				ingredient1->openEffect(i->first);
				ingredient2->openEffect(i->first);

				break;
			}
		}

		if (res)
			break;
	}
}
