#pragma once
#include "EffectsTable.h"
#include "AlchemyProgramParser.h"
#include "EffectBuilder.h"

// ��������� ������� ��������
class EffectsTableBuilder
{
public:

	EffectsTableBuilder();

	void setEffectstable(AlchemyProgramParser* alchemyProgramParser);

private:

	EffectsTable* effectstable;

	EffectBuilder* effectBuilder;

	// �������� ���������� �������
	void addPositiveEffects(int numberOfEffects);
};

