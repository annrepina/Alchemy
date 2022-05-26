#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder()
{
	effectstable = new EffectsTable();
	effectBuilder = nullptr;
}

void EffectsTableBuilder::setEffectstable(AlchemyProgramParser* alchemyProgramParser)
{
	// ������

	// ���� ��� ��� ������ � �� ����������

	// ������� ������� ����

	// ������� ������ ��������� ������������
	effectBuilder = new EffectBuilder();
}

void EffectsTableBuilder::addPositiveEffects(int numberOfEffects)
{
	// ��������� ������ � ������ ���� � ��������
	int lastIndex = NUMBER_OF_POSITIVE_EFFECTS - 1;

	// � ����� ��������� ������ ���� � ����
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildPositiveEffect(lastIndex);

		this->effectstable->addEffect(this->effectBuilder->getResult());

		// ��������� ��������� ������
		--lastIndex;
	}
}
