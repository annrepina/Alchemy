#pragma once
#include "BinaryReader.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryReader.h"
#include "EffectsTableBinaryReader.h"
#include "IngredientsTableBinaryReader.h"
#include "PotionTableBinaryReader.h"

// �����, ������� ������ ����� AlchemyLogic �� ��������� �����
class AlchemyLogicReader : public BinaryReader< AlchemyLogic>
{
public:

	// ����������� �� ���������
	AlchemyLogicReader();

	// ����������
	~AlchemyLogicReader();

	// ������ �� ��������� �����
	AlchemyLogic* readFromFile(string path, ifstream& stream);

private:

	// �����, ������� ������ ����� Alchemist �� ��������� �����
	AlchemistBinaryReader* alchemistBinaryReader;

	// �����, ������� ������ ����� EffectsTable �� ��������� �����
	EffectsTableBinaryReader* effectsTableBinaryReader;

	// �����, ������� ������ ����� IngredientsTable �� ��������� �����
	IngredientsTableBinaryReader* ingredientsTableBinaryReader;

	// �����, ������� ������ ����� PotionTable �� ��������� �����
	PotionTableBinaryReader* potionTableBinaryReader;

	// �������� ������
	void clear() override;
};

