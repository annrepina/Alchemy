#include "EffectBinaryWriter.h"

EffectBinaryWriter::EffectBinaryWriter()
{

}

EffectBinaryWriter::~EffectBinaryWriter()
{
	clear();
}

void EffectBinaryWriter::write(ofstream& stream, string filePath, Effect* effect) const
{
	BinaryWriter::write(stream, filePath, effect);

	// �������� ���
	string name = effect->getName();
	// ����� ��� 
	writeString(stream, name);

	// �������� ������ ����������, ���������� ���������� ��� ���������� ������
	bool isPositive = effect->getIsPositive();
	writeBool(stream, isPositive);
}

void EffectBinaryWriter::clear()
{
}
