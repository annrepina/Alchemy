#pragma once
#include "BinaryReader.h"
#include "EffectsTable.h"
#include "EffectBinaryReader.h"

// �����, ������� ������ ����� EffectsTable �� ��������� �����
class EffectsTableBinaryReader : public BinaryReader<EffectsTable>
{
public:

	// ����������� �� ���������
	EffectsTableBinaryReader();

	// ����������
	~EffectsTableBinaryReader() override;

	// ������ �� ��������� �����
	EffectsTable* readFromFile(string path, ifstream& stream) override;

private:

	// �������� ������
	void clear() override;
};

