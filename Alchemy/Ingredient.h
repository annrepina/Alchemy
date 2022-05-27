#pragma once

#include "Effect.h"
#include <vector>

#define NUMBER_OF_EFFECTS 2

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

	// �������� id ������� �� ������
	int getEffectId(int number);

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
	float price;

	// ������ ���������� �� 2� ������������
	vector<int> effectsId;

	//// ����� ������� ������
	//void clear();
};

