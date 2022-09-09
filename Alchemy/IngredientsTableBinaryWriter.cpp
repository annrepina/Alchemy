#include "IngredientsTableBinaryWriter.h"

IngredientsTableBinaryWriter::IngredientsTableBinaryWriter()
{
}

IngredientsTableBinaryWriter::~IngredientsTableBinaryWriter()
{
	clear();
}

void IngredientsTableBinaryWriter::write(ofstream& stream, string filePath, IngredientsTable* ingredientsTable) const
{
	BinaryWriter::write(stream, filePath, ingredientsTable);


	// ��������� ������������ ��������, ��, � ������� ���-�� ������ ����
	vector<int> availableElements;

	// Id �����������
	static int id;

	// �����������
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();
}

void IngredientsTableBinaryWriter::clear()
{
}
