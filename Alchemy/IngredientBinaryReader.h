#pragma once
#include "BinaryReader.h"
#include "Ingredient.h"

// �����, ������� ������ ����� Ingredient �� ��������� �����
class IngredientBinaryReader : public BinaryReader<Ingredient>
{
public:

	// ����������� �� ���������
	IngredientBinaryReader();

	// ����������
	~IngredientBinaryReader();

	// ������ �� ��������� �����
	Ingredient* readFromFile(string path, ifstream& stream) override;

protected: 

	// �������� �� ������
	void clear() override;
};

