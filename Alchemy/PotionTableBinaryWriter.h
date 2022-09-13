#pragma once
#include "BinaryWriter.h"
#include "PotionTable.h"
#include "PotionBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

// �����,������� ����� ����� PotionTable � ���� � �������� ����
class PotionTableBinaryWriter : public BinaryWriter<PotionTable>
{
public:

	// ����������� �� ���������
	PotionTableBinaryWriter();

	// ����������
	~PotionTableBinaryWriter();

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string path, PotionTable* potionTable) const override;

private:

	// ������ ������
	void clear() override;

	// �����,������� ����� ����� Potion � ���� � �������� ����
	PotionBinaryWriter* potionBinaryWriter;

	// �����,������� ����� ����� EffectsTable � ���� � �������� ����
	EffectsTableBinaryWriter* effectsTableBinaryWriter;
};