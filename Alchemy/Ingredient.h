#pragma once

#include "Effect.h"
//#include <vector>
#include <map>

#define NUMBER_OF_EFFECTS			2		// ���-�� ��������

#define MIN_PRICE					4		// ����������� ���� �����������
#define MAX_PRICE					135		// ������������ ���� �����������

#define UNKNOWN						false	// ����������� ������������ ������	

// ����� ����������
class Ingredient
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

	// �������� id ������� �� ������
	int getEffectId(int number);
	
	// �������� ���
	string getName();

	// �������� ���-��
	int getNumber();

#pragma endregion �������

	//// ����������� � �����������
	//Ingredient(string name, float price, vector<Effect*> effects);

#pragma endregion ������������

#pragma region �������

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ����
	void setPrice(float price);

	//// ������ ��� id
	//void setId(int id);

#pragma endregion �������

	// �������� ������
	void addEffect(int effectId);

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

