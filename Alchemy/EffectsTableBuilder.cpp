#include "EffectsTableBuilder.h"

EffectsTableBuilder::EffectsTableBuilder() : AlchemyTableBuilder()
{
	/*reset();*/
	//effectBuilder = new EffectBuilder();
	effectBuilder = nullptr;
}

EffectsTableBuilder::~EffectsTableBuilder()
{
	clear();
}

void EffectsTableBuilder::buildTable(AlchemyProgramParser* alchemyProgramParser)
{
	// ������

	// ���� ��� ��� ������ � �� ����������

	// ������� ������� ����

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
//
//EffectsTable* EffectsTableBuilder::getResult()
//{
//	EffectsTable* res = this->effectsTable;
//
//	reset();
//
//	return res;
//}
//
//void EffectsTableBuilder::reset()
//{
//	effectsTable = new EffectsTable();
//}

void EffectsTableBuilder::clear()
{
	//if (nullptr != this->effectsTable)
	//{
	//	delete this->effectsTable;
	//	this->effectsTable = nullptr;
	//}

	AlchemyTableBuilder::clear();

	if (nullptr != this->effectBuilder)
	{
		delete this->effectBuilder;
		this->effectBuilder = nullptr;
	}
}
