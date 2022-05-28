#pragma once
#include "EffectsTable.h"
#include "AlchemyProgramParser.h"
#include "EffectBuilder.h"
#include "AlchemyTableBuilder.h"

// ��������� ������� ��������
class EffectsTableBuilder : public AlchemyTableBuilder
{
public:

	// ����������� �� ���������
	EffectsTableBuilder();

	//// ����������
	~EffectsTableBuilder() override;

	// ������ ������� ��������
	void buildTable(AlchemyProgramParser* alchemyProgramParser) override;

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
	void reset() override;

	// ������� ������
	void clear() override;

};

