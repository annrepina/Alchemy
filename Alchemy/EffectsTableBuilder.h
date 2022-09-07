#pragma once
#include "EffectsTable.h"
#include "AlchemyLogicWriter.h"
#include "EffectBuilder.h"
#include "AlchemyTableBuilder.h"

// ��������� ������� ��������
class EffectsTableBuilder : public AlchemyTableBuilder<EffectsTable>
{
public:

	// ����������� �� ���������
	EffectsTableBuilder();

	//// ����������
	~EffectsTableBuilder() override;

	// ������ ������� ��������
	void buildTable(AlchemyLogicWriter* alchemyLogicWriter) override;

	//// �������� ���������� �������
	//void addPositiveEffects(int numberOfEffects);

	//// �������� ���������� �������
	//void addNegativeEffects(int numberOfEffects);

	//// �������� ���������
	//EffectsTable* getResult();

private:

	//EffectsTable* effectsTable;

	EffectBuilder* effectBuilder;

	// �������� �������
	void addEffects(int numberOfEffects, bool isPositive);

	//// ���������� �� ��������� ���������
	//void reset() override;

	// ������� ������
	void clear() override;

};

