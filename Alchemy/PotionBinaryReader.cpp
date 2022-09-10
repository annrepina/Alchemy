#include "PotionBinaryReader.h"

PotionBinaryReader::PotionBinaryReader()
{
}

PotionBinaryReader::~PotionBinaryReader()
{
	clear();
}

Potion* PotionBinaryReader::readFromFile(string path, ifstream& stream)
{
	if (stream.is_open())
	{
		Potion* potion = new Potion();

		// ������ id �������
		int effectId = readInt(stream);
		potion->setEffectId(effectId);

		// ������ ����
		int price = readInt(stream);
		potion->setPrice(price);

		// ������ ���-��
		int number = readInt(stream);
		potion->setNumber(number);

		// ������ �������� �����
		int power = readInt(stream);
		potion->setPower(power);

		return potion;
	}

	return nullptr;
}

void PotionBinaryReader::clear()
{
}
