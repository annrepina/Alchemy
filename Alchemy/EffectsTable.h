#pragma once
#include "Effect.h"
#include "Table.h"
#include <map>

// ������� �������� ������������
class EffectsTable : public Table<Effect>
{
public:

	// ����������� �� ���������
	EffectsTable();

	~EffectsTable() override;

	// �������� ������
	void add(Effect* effect) override;

	// ������ �������
	void print();

	// ������ ��� �������
	int getSize();

	// �������� ������ �� �����
	Effect* getEffectByKey(int key);

private:

	// Id �������
	static int id;

	// ������ �������
	int size;

	// ������ ��������
	map<int, Effect*> effectsWithId;

	// ������� ������
	void clear();
};

