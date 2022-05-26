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

	// �������� �������
	void addEffects(int numberOfEffects, bool isPositive);

	//// �������� ���������� �������
	//void addPositiveEffects(int numberOfEffects);

	//// �������� ���������� �������
	//void addNegativeEffects(int numberOfEffects);

private:

	EffectsTable* effectstable;

	EffectBuilder* effectBuilder;


};

