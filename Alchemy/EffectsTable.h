#pragma once
#include "Effect.h"
#include <map>

// ������� �������� ������������
class EffectsTable
{
public:

	// ����������� �� ���������
	EffectsTable();

	~EffectsTable();

	// �������� ������
	void addEffect(Effect* effect);

	// ������ �������
	void print();

	// ������ ��� �������
	int getSize();

	// �������� ������ �� �����
	Effect* getEffectByKey(int key);

private:

	// ������ ��������
	//vector<Effect*> effects;

	// Id �������
	static int id;

	// ������ �������
	int size;

	// ������ ��������
	map<int, Effect*> effectsWithId;

	// ������� ������
	void clear();
};

