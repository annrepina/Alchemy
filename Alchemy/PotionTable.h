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

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

#pragma region �������

	// �������� �������� �� ��������� ������� � map
	map<int, Potion*>::iterator getEndIterator();

	// �������� �������� �� ��������� ������� � map
	map<int, Potion*>::iterator getStartIterator();

	EffectsTable* getEffectsTable();

#pragma endregion �������

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

