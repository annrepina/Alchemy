#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>
#include "IObservable.h"

//#define NUMBER_OF_COLUMNS			6		// ���-�� �������
//#define OUTER_BORDERS				2		// ������� ������� ������� (����� � ������)

//#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

// ������� ������������
class IngredientsTable : public Table<Ingredient>, public IObservable, public IObserver
{
public:

	// ����������� �� ���������
	IngredientsTable();

	~IngredientsTable() override;

	// �������� ���������� � �������
	void add(Ingredient* ingredient) override;

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	void update(int id, bool isNewElement) override;

	void update(int id, int previousNumber) override;

	void update() override;

#pragma region �������

	// �������� �������� �� ��������� ������� � map
	map<int, Ingredient*>::iterator getEndIterator();

	// �������� �������� �� ������ ������� � map
	map<int, Ingredient*>::iterator getStartIterator();

	//// �������� map
	//map<int, Ingredient*> getIngredientsWithId();

	// �������� ������� ��������
	EffectsTable* getEffectsTable();

	// �������� ���������� �� id 
	Ingredient* getIngredientById(int id);

	// �������� ���������� �� id 
	Ingredient* getIngredientByName(string name);

	// �������� ���� �� ��������
	int getIdByIngredient(Ingredient* ingredient);

#pragma endregion �������

	//void subscribe(IObserver* observer) override;

	//void unsubscribe(IObserver* observer) override;

	//void notify(int id) override;

	// ��������� ���-�� �����������
	void decreaseNumberOfIngredient(int ingredientId, int number);

private:

	// Id �����������
	static int id;

	// �����������
	map<int, Ingredient*> ingredientsWithId;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������ ������
	void clear();
};

