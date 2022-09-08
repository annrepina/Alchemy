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

	// �������� ������
	void add(Effect* effect, int id) override;

	// ������ �������
	void print();

#pragma region �������

	int getId();

	// ������ ��� �������
	int getSize();

	// �������� ������ �� �����
	Effect* getEffectByKey(int key);

	// �������� �������� �� ������ map
	map<int, Effect*>::iterator getStartIterator();
	
	// �������� �������� �� ������ map
	map<int, Effect*>::iterator getEndIterator();

#pragma endregion �������

#pragma region �������

	void setId(int id);

#pragma endregion �������

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

