#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"
#include "IObservable.h"

// ����� ������� �����
class PotionTable : public Table<Potion>, public IObservable, public IObserver
{
public:

	// ����������� �� ���������
	PotionTable();

	// ����������
	~PotionTable() override;

	// �������� ����� � �������
	void add(Potion* potion) override;

	// �������� ����� � ������� � id 
	void add(Potion* element, int id) override;

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ������ ��� ������ id 
	void setId(int id);

	// ���������� id �����, ���� ����� ����, ����� -1
	int hasSuchPotion(Potion* potion);

	// ��������� ������� ������ �� ��������� ������� �������� - Potion
	void update(int id, bool isNewElement) override;

	// ��������� ������� ������ �� ��������� ������� �������� - Potion
	void update(int id, int previousNumber) override;

	// ��������� ������� ������ �� ��������� ������� �������� - Potion
	void update() override;

	// ��������� ���-�� �����
	void decreaseNumberOfPotion(int potionId, int number);

#pragma region �������

	// �������� �������� �� ��������� ������� � map potiontsWithId
	map<int, Potion*>::iterator getEndIterator();

	// �������� �������� �� ��������� ������� � map potiontsWithId
	map<int, Potion*>::iterator getStartIterator();

	// �������� ������� ��������
	EffectsTable* getEffectsTable();

	// �������� ����� �� id
	Potion* getPotionById(int id);

	// �������� ������ ������� (���-�� ���������)
	int getSize();

	// �������� ������ id 
	int getId();

#pragma endregion �������

private:

	// Id ����� ���������� �����
	static int id;

	// ����������� � id 
	map<int, Potion*> potiontsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();
};