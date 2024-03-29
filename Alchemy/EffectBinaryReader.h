#pragma once
#include "BinaryReader.h"
#include "Effect.h"

// �����, ������� ������ ����� Effect �� ��������� �����
class EffectBinaryReader : public BinaryReader<Effect>
{
public:

	// ����������� �� ���������
	EffectBinaryReader();

	// ����������
	~EffectBinaryReader() override;

	// ������ �� ��������� �����
	Effect* readFromFile(string path, ifstream& stream) override;

private:

	// �������� ������
	void clear() override;
};

