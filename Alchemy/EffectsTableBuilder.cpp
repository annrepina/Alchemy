#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder()
{
	effectstable = new EffectsTable();
	effectBuilder = new EffectBuilder();
}

void EffectsTableBuilder::setEffectstable(AlchemyProgramParser* alchemyProgramParser)
{
	// ������

	// ���� ��� ��� ������ � �� ����������

	// ������� ������� ����

	// ������� ������ ��������� ������������
	effectBuilder = new EffectBuilder();
}

void EffectsTableBuilder::addEffects(int numberOfEffects, bool isPositive)
{
	// ��������� ������ � ������ ���������� ��������
	int lastIndex = numberOfEffects - 1;

	// � ����� ��������� ������� � �������
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildEffect(lastIndex, isPositive);

		this->effectstable->addEffect(this->effectBuilder->getResult());

		// ��������� ��������� ������
		--lastIndex;
	}
}

//void EffectsTableBuilder::addPositiveEffects(int numberOfEffects)
//{
//	// ��������� ������ � ������ ���������� ��������
//	int lastIndex = NUMBER_OF_POSITIVE_EFFECTS - 1;
//
//	// � ����� ��������� ������� � �������
//	for (int i = 0; i < numberOfEffects; ++i)
//	{
//		this->effectBuilder->buildPositiveEffect(lastIndex);
//
//		this->effectstable->addEffect(this->effectBuilder->getResult());
//
//		// ��������� ��������� ������
//		--lastIndex;
//	}
//}
//
//void EffectsTableBuilder::addNegativeEffects(int numberOfEffects)
//{
//	// ��������� ������ � ������ ���������� ��������
//	int lastIndex = NUMBER_OF_NEGATIVE_EFFECTS - 1;
//
//	// � ����� ��������� ������� � �������
//	for (int i = 0; i < numberOfEffects; ++i)
//	{
//		this->effectBuilder->buildNegativeEffect(lastIndex);
//
//		this->effectstable->addEffect(this->effectBuilder->getResult());
//
//		// ��������� ��������� ������
//		--lastIndex;
//	}
//}
