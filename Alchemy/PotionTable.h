#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"
#include "IObservable.h"

// ����� ������� �����
class PotionTable : public Table<Potion>, public IObservable, public IObserver
{
public:

	PotionTable();

	~PotionTable() override;

	// �������� ����� � �������
	void add(Potion* potion) override;

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ���������� ���� �����, ���� ����� ����, ����� -1
	int hasSuchPotion(Potion* potion);

	void update(int id, bool isNewElement) override;

	void update(int id, int previousNumber) override;

#pragma region �������

	// �������� �������� �� ��������� ������� � map
	map<int, Potion*>::iterator getEndIterator();

	// �������� �������� �� ��������� ������� � map
	map<int, Potion*>::iterator getStartIterator();

	EffectsTable* getEffectsTable();

	// �������� ����� �� id
	Potion* getPotionById(int id);

	//// �������� ����� �� �����
	//Potion* getSuchPotion(Potion* potion);

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

