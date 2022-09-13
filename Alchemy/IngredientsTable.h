#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>
#include "IObservable.h"

// ������� ������������
class IngredientsTable : public Table<Ingredient>, public IObservable, public IObserver
{
public:

	// ����������� �� ���������
	IngredientsTable();

	// ����������
	~IngredientsTable() override;

	// �������� ���������� � �������
	void add(Ingredient* ingredient) override;

	// �������� ���������� � ������� � id
	void add(Ingredient* element, int id) override;

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ������ ��� id 
	void setId(int id);

	// �������� ������� ��-�� ��������� ����� ������� �������� - �����������
	void update(int id, bool isNewElement) override;

	// �������� ������� ��-�� ��������� ����� ������� �������� - �����������
	// ��������� �����, ����� ���� ���-�� ������������ == 0, ������� id ����������� �� ��������� ���������
	void update(int id, int previousNumber) override;

	// �������� ������� ��-�� ��������� ����� ������� �������� - �����������
	void update() override;

#pragma region �������

	// �������� �������� �� ��������� ������� � map ingredientsWithId
	map<int, Ingredient*>::iterator getEndIterator();

	// �������� �������� �� ������ ������� � map ingredientsWithId
	map<int, Ingredient*>::iterator getStartIterator();

	// �������� ������� ��������
	EffectsTable* getEffectsTable();

	// �������� ���������� �� id 
	Ingredient* getIngredientById(int id);

	// �������� ���������� �� �����
	Ingredient* getIngredientByName(string name);

	// �������� ���� �� �������� �����������
	int getIdByIngredient(Ingredient* ingredient);

	// �������� ������ id 
	int getId();

#pragma endregion �������

	// ��������� ���-�� �����������
	void decreaseNumberOfIngredient(int ingredientId, int number);

private:

	// Id ����� ���������� �����������
	static int id;

	// ����������� � �� id 
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();
};