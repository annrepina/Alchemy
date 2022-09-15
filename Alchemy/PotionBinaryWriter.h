#pragma once
#include "BinaryWriter.h"
#include "Potion.h"

// �����,������� ����� ����� Potion � ���� � �������� ����
class PotionBinaryWriter : public BinaryWriter<Potion>
{
public:

	// ����������� �� ���������
	PotionBinaryWriter();

	// ����������
	~PotionBinaryWriter() override;

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string path, Potion* potion) const override;

private:

	// ������ ������
	void clear() override;

};