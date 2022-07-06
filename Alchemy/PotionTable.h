#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"

// ����� ������� �����
class PotionTable : public Table<Potion>
{
public:

	PotionTable();

	~PotionTable() override;

	// �������� ����� � �������
	void add(Potion* potion) override;

private:

	// Id �����
	static int id;

	// �����������
	map<int, Potion*> potiontsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();
};

