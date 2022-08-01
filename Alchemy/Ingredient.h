#pragma once
#include "Effect.h"
#include "IObservable.h"
#include <map>

#define NUMBER_OF_EFFECTS			2		// ���-�� ��������

#define MIN_PRICE					4		// ����������� ���� �����������
#define MAX_PRICE					135		// ������������ ���� �����������

#define UNKNOWN						false	// ����������� ������������ ������	
#define KNOWN						true	// ��������� ������������ ������

// ����� ����������
class Ingredient : public IObservable
{
public:

#pragma region ������������

	// ����������� �� ���������
	Ingredient();

	// ����������
	~Ingredient();

	// ������
	void print();

#pragma region �������

	// ������ �������� �� ������������ ������ � ������� ����������� �� ������ �������
	bool getEffectIsKnown(int number);

	// �������� �������� �� ������ �������������� �������
	map<int, bool>::iterator getBeginIteratorOfEffectsId();

	// �������� �������� �� ����� �������������� �������
	map<int, bool>::iterator getEndIteratorOfEffectsId();
	
	// �������� ���
	string getName();

	// �������� ���-��
	int getNumber();

	// ������ ��� ����
	int getPrice();

#pragma endregion �������

	//// ����������� � �����������
	//Ingredient(string name, float price, vector<Effect*> effects);

#pragma endregion ������������

#pragma region �������

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ����
	void setPrice(float price);

	// ������ ��� ���-��
	void setNumber(int number);

	// ������� ������ �� id
	void openEffect(int id);

	//// ������ ��� id
	//void setId(int id);

#pragma endregion �������

	// �������� ������
	void addEffect(int effectId);

	// ��������� ���-�� ����������� �� ����� �����
	void increaseNumber(int number);

	// ��������� ���-�� ������������ �� 1
	void decreaseNumber();

private:

	//// ������� ������������
	//static int counter;

	//// id �����������
	//int id;
	
	// �������� �����������
	string name;

	// ���� �� ����������
	int price;

	// ���-��
	int number;

	//// ������ ���������� �� 2� ������������
	//vector<int> effectsId;

	// ������ �������� �� 2� ������������ � �� �������� ����������� ������
	map<int, bool> effectsId;

	//// ����� ������� ������
	//void clear();
};

