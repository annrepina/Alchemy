#include "PotionBinaryWriter.h"

PotionBinaryWriter::PotionBinaryWriter()
{
}

PotionBinaryWriter::~PotionBinaryWriter()
{
	clear();
}

void PotionBinaryWriter::write(ofstream& stream, string path, Potion* potion) const
{
	BinaryWriter::write(stream, path, potion);

	// �������� � ����� id �������
	int effectId = potion->getEffectId();
	writeInt(stream, effectId);

	// �������� � ����� ����
	int price = potion->getPrice();
	writeInt(stream, price);

	// �������� � ����� ���-��
	int number = potion->getNumber();
	writeInt(stream, number);

	// �������� � ����� �������� �����
	int power = potion->getPower();
	writeInt(stream, power);
}

void PotionBinaryWriter::clear()
{
}
