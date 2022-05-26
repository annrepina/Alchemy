#pragma once
#include "Effect.h"

#define NUMBER_OF_POSITIVE_EFFECTS	35		// ���-�� ���������� ��������
#define NUMBER_OF_NEGATIVE_EFFECTS	20		// ���-�� ���������� ��������

// ��������� ��������
class EffectBuilder
{
public:

	// ����������� �� ���������
	EffectBuilder();

	// ����������
	~EffectBuilder();

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ��������� ���������� ������������� �� ������
	void setIsPositive(bool isPositive);

	// ������� ������
	void buildEffect(int lastIndex, string listOfEffectsNames[], bool isPositive);

	// ������� ���������� ������
	void buildPositiveEffect(int lastIndex);

	// ������� ���������������� ������
	void buildNegativeEffect(int lastIndex);

	// �������� ��������� �������������
	Effect* getResult();

private:

	// ��������� �������
	Effect* effect;

	// �������� �� ��������� ���������
	void reset();

	// ������ ������ (���������������� ������)
	void clear();

	// ������� ���
	string chooseEffectName(int lastIndex, string listOfEffectsNames[]);

	// ������ ���� ������������� ��������
	static string listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS];

	// ������ ���� ������������� ��������
	static string listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS];
};

