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

	// ����������
	~EffectsTableBuilder() override;

	// ������ ������� ��������
	void buildTable() override;

private:

	// ��������� ��������
	EffectBuilder* effectBuilder;

	// �������� �������
	void addEffects(int numberOfEffects, bool isPositive);

	// ������� ������
	void clear() override;

};