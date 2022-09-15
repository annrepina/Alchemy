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
	// ������� ������ ��������� ������������
	effectBuilder = new EffectBuilder();

	// �������� �������
	addEffects(NUMBER_OF_POSITIVE_EFFECTS, POSITIVE);
	addEffects(NUMBER_OF_NEGATIVE_EFFECTS, NEGATIVE);
}

void EffectsTableBuilder::addEffects(int numberOfEffects, bool isPositive)
{
	// ��������� ������ � ������ ��������
	int lastIndex = numberOfEffects - 1;

	// � ����� ��������� ������� � �������
	for (int i = 0; i < numberOfEffects; ++i)
	{
		this->effectBuilder->buildEffect(lastIndex, isPositive);

		this->element->add(this->effectBuilder->getResult());

		// ��������� ��������� ������
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