#pragma once
#include "EffectsTable.h"
#include "AlchemyProgramParser.h"
#include "EffectBuilder.h"

// ��������� ������� ��������
class EffectsTableBuilder
{
public:

	// ����������� �� ���������
	EffectsTableBuilder();

	// ����������
	~EffectsTableBuilder();

	// ������ ������� ��������
	void buildEffectstable(AlchemyProgramParser* alchemyProgramParser);

	//// �������� ���������� �������
	//void addPositiveEffects(int numberOfEffects);

	//// �������� ���������� �������
	//void addNegativeEffects(int numberOfEffects);

	// �������� ���������
	EffectsTable* getResult();

private:

	EffectsTable* effectsTable;

	EffectBuilder* effectBuilder;

	// �������� �������
	void addEffects(int numberOfEffects, bool isPositive);

	// ���������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();


};

