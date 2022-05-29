#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>

//#define NUMBER_OF_COLUMNS			6		// ���-�� �������
//#define OUTER_BORDERS				2		// ������� ������� ������� (����� � ������)

//#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

// ������� ������������
class IngredientsTable : public Table<Ingredient>
{
public:

	// ����������� �� ���������
	IngredientsTable();

	~IngredientsTable() override;

	// �������� ���������� � �������
	void add(Ingredient* ingredient) override;

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	//// ������ �������
	//void print();

	// �������� �������� �� ��������� ������� � map
	map<int, Ingredient*>::iterator getEndIterator();

	// �������� �������� �� ������ ������� � map
	map<int, Ingredient*>::iterator getStartIterator();

	// �������� map
	map<int, Ingredient*> getIngredientsWithId();

	// �������� ������� ��������
	EffectsTable* getEffectsTable();


	// ��������� ����� �������
	//void calculateLength();



private:

	// Id �����������
	static int id;

	// �����������
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();



	//// ������� ���������� id
	//int calculateMaxIdStrSize();

	//// ������� ����� ������� �������� �����������
	//int calculateMaxNameSize();

	//// ������� ���������� ���-�� ������������
	//int calculateMaxNumberStrSize();

	//// ��������� ������� ������������ ���� ��������
	//int calculateMaxEffectNameSize();

	//// ������ ������������ ������� ���� ��������
	//int effectsNameSizes[NUMBER_OF_EFFECTS];

};

