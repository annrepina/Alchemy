#pragma once
#include "BinaryWriter.h"
#include "EffectsTable.h"
#include "EffectBinaryWriter.h"

// �����,������� ����� ����� EffectsTable � ���� � �������� ����
class EffectsTableBinaryWriter : public BinaryWriter<EffectsTable>
{
public:

	// ����������� �� ���������
	EffectsTableBinaryWriter();

	// ����������
	~EffectsTableBinaryWriter() override;

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string filePath, EffectsTable* effectsTable) const override;

protected:

	// ������ ������
	void clear() override;

	// �����,������� ����� ����� Effect � ���� � �������� ����
	EffectBinaryWriter* effectBinaryWriter;
};

