#include "EffectBinaryWriter.h"

EffectBinaryWriter::EffectBinaryWriter(Effect* effect, string filePath) : BinaryWriter(effect, filePath)
{

}

EffectBinaryWriter::~EffectBinaryWriter()
{
	clear();
}

void EffectBinaryWriter::write(ofstream& stream) const
{
	BinaryWriter::write(stream);

	// �������� ���
	string name = object->getName();
	// ����� ��� 
	writeString(stream, name);

	// �������� ������ ����������, ���������� ���������� ��� ���������� ������
	bool isPositive = object->getIsPositive();
	writeBool(stream, isPositive);
}

void EffectBinaryWriter::clear()
{
}
