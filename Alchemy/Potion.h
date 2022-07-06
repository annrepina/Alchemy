#pragma once
#include "Ingredient.h"
//#include "EffectsTable.h"

// ����� - �����
class Potion
{
public:

	// ����������� �� ���������
	Potion();

	//// ����������� � �����������
	//Potion(Ingredient* ingredient1, Ingredient* ingredient2);

	void setEffectId(int id);

	void setPrice(int price);

	void setNumber(int number);

private:

	// id �������
	int effectId;

	// ����
	int price;

	// ���-��
	int number;

	//// ���� ���� �� � ������������ ���������� �� ��������
	//bool hasEffectsMatching(Ingredient* ingredient1, Ingredient* ingredient2);

};