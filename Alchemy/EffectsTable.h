#pragma once
#include "Effect.h"
#include <map>

// ������� �������� ������������
class EffectsTable
{
public:

	// 
	EffectsTable();

	~EffectsTable();

	// �������� ������
	void addEffect(Effect* effect);

	// ������ �������
	void print();

private:

	// ������ ��������
	//vector<Effect*> effects;

	// Id �������
	static int id;

	// ������ ��������
	map<int, Effect*> effectsWithId;

	// ������� ������
	void clear();
};

