#include "IngredientBinaryWriter.h"

IngredientBinaryWriter::IngredientBinaryWriter()
{
}

IngredientBinaryWriter::~IngredientBinaryWriter()
{
	clear();
}

void IngredientBinaryWriter::write(ofstream& stream, string filePath, Ingredient* ingredient) const
{
	BinaryWriter::write(stream, filePath, ingredient);

	// �������� � ����� �������� �����������
	string name = ingredient->getName();
	writeString(stream, name);

	// ������� � ����� ���� �� ����������
	int price = ingredient->getPrice();
	writeInt(stream, price);

	// �������� � ����� ���-�� ������������
	int number = ingredient->getNumber();
	writeInt(stream, number);

	// �������� ���-�� �������� � ����� ���
	int numberOfEffects = ingredient->getNumberOfEffects();
	writeInt(stream, numberOfEffects);

	// �������� ���������
	auto beginIter = ingredient->getBeginIteratorOfEffectsId();
	auto endIter = ingredient->getEndIteratorOfEffectsId();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// �������� ���� (id �����������) � �����
		int key = i->first;
		writeInt(stream, key);

		// �������� ������, ���������� �� ������������
		bool isPositive = i->second;
		writeBool(stream, isPositive);
	}
}

void IngredientBinaryWriter::clear()
{
}
