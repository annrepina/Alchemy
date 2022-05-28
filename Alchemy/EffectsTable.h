#pragma once
#include "Effect.h"
#include "Table.h"
#include <map>

// ������� �������� ������������
class EffectsTable : public Table
{
public:

	// ����������� �� ���������
	EffectsTable();

	~EffectsTable() override;

	// �������� ������
	void addEffect(Effect* effect);

	// ������ �������
	void print() const override;

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

