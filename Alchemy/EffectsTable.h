#pragma once
#include "Effect.h"
#include <vector>

// ������� �������� ������������
class EffectsTable
{
public:

	EffectsTable();

	// �������� ������
	void addEffect(Effect* effect);

private:

	// ������ ��������
	vector<Effect*> effects;
};

