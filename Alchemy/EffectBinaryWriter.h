#pragma once
#include "BinaryWriter.h"
#include "Effect.h"

// �����,������� ����� ����� Effect � ���� � �������� ����
class EffectBinaryWriter : public BinaryWriter<Effect>
{
public:

	// ����������� �� ���������
	EffectBinaryWriter();

	// ����������
	~EffectBinaryWriter() override;

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string filePath, Effect* effect) const override;

private:

	// ������ ������
	void clear() override;
};

