#pragma once
#include "Effect.h"
#include "Builder.h"

#define TOTAL_NUMBER_OF_EFFECTS		55		// ����� ���-�� ��������
#define NUMBER_OF_POSITIVE_EFFECTS	35		// ���-�� ���������� ��������
#define NUMBER_OF_NEGATIVE_EFFECTS	20		// ���-�� ���������� ��������

#define POSITIVE					true	// ���������� ������
#define NEGATIVE					false	// ���������� ������

// ��������� ��������
class EffectBuilder : public Builder<Effect>
{
public:

	// ����������� �� ���������
	EffectBuilder();

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ��������� ���������� ������������� �� ������
	void setIsPositive(bool isPositive);

	// ������� ������
	void buildEffect(int lastIndex, bool IsPositive);

	// ������� ������ - ����������
	void buildEffect(int lastIndex, string listOfEffects[], bool isPositive);

private:

	// ������� ��� �������
	string chooseEffectName(int lastIndex, string listOfEffectsNames[]);

	// ������ ���� ������������� ��������
	static string listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS];

	// ������ ���� ������������� ��������
	static string listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS];
};