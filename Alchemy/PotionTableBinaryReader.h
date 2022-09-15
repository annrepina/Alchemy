#pragma once
#include "BinaryReader.h"
#include "PotionTable.h"
#include "PotionBinaryReader.h"
#include "EffectsTableBinaryReader.h"

// �����, ������� ������ ����� PotionTable �� ��������� �����
class PotionTableBinaryReader : public BinaryReader<PotionTable>
{
public:

	// ����������� �� ���������
	PotionTableBinaryReader();

	// ����������
	~PotionTableBinaryReader() override;

	// ������ �� ��������� �����
	PotionTable* readFromFile(string path, ifstream& stream) override;

private:

	// �������� ������
	void clear() override;

	// �����, ������� ������ ����� Potion �� ��������� �����
	PotionBinaryReader* potionBinaryReader;

	// �����, ������� ������ ����� EffectsTable �� ��������� �����
	EffectsTableBinaryReader* effectsTableBinaryReader;
};

