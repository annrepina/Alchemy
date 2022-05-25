#pragma once
#include "Effect.h"

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

	// �������� ��������� �������������
	Effect* getResult();

private:

	// ��������� �������
	Effect* effect;

	// �������� �� ��������� ���������
	void reset();

	// ������ ������ (���������������� ������)
	void clear();
};

