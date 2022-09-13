#pragma once
#include "BinaryWriter.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"
#include "IngredientsTableBinaryWriter.h"
#include "PotionTableBinaryWriter.h"

// �����,������� ����� ����� AlchemyLogic � ���� � �������� ����
class AlchemyLogicWriter : public BinaryWriter<AlchemyLogic>
{
public:

	// ����������� �� ���������
	AlchemyLogicWriter();

	// ����������
	~AlchemyLogicWriter();

	// ����� � ���� � �������� ����
	void write(ofstream& stream, string filePath, AlchemyLogic* alchemyLogic) const override;

protected:

	// �����,������� ����� ����� Alchemist � ���� � �������� ����
	AlchemistBinaryWriter* alchemistBinaryWriter;

	// �����,������� ����� ����� EffectsTable � ���� � �������� ����
	EffectsTableBinaryWriter* effectsTableBinaryWriter;

	// �����,������� ����� ����� IngredientsTable � ���� � �������� ����
	IngredientsTableBinaryWriter* ingredientsTableBinaryWriter;

	// �����,������� ����� ����� PotionTable � ���� � �������� ����
	PotionTableBinaryWriter* potionTableBinaryWriter;

	// �������� ������
	void clear() override;

};